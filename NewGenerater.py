import os
import io
import json
import logging
Log_level = logging.DEBUG
enmptyConf = '''
{
    "template_path": "",
    "exclude_files": [],
    "exclude_folders": [],
    "output_file": "",
    "ignore_empty_dir": true,
    "comment_ignore_end": "</ignore>",
    "comment_ignore_begin": "<ignore>",
    "comment_marking_end": "</genHead>",
    "comment_marking_begin": "<genHead>",
    "support_text_format": [],
    "support_language": {}
}
'''

def srcCmp(name : str) -> int:
    ret = 0
    for i in range(0,len(name)):
        if not name[i].isdigit():
            break
        ret*=10; ret+=int(name[i])
    return ret

def AnalysisCode(fileContent :str, codeType :str, filePath :str, profile :json):
    # f == 0 and f1 == 0代表正文
    # f != 0代表文档注释
    # f1 != 0代表需要在markdown生成的时候需要被忽视的信息(比如不必要的题目信息等)
    f = 0
    f1 = 0
    fail = 0
    head = ''
    content = ''
    fileLines = fileContent.split('\n')
    comment_ignore_end = profile['comment_ignore_end']
    comment_ignore_begin = profile['comment_ignore_begin']
    comment_marking_end = profile['comment_marking_end']
    comment_marking_begin = profile['comment_marking_begin']
    for line in fileLines:
        if comment_ignore_begin in line:
            f1 += 1
            if f1 < 0 or f1 > 1:
                fail = 1
        elif comment_ignore_end in line:
            f1 -= 1
            if f1 < 0 or f1 > 1:
                fail = 1
        elif comment_marking_begin in line:
            f += 1
            if f < 0 or f > 1:
                fail = 1
        elif comment_marking_end in line:
            f -= 1
            if f < 0 or f > 1:
                fail = 1
        else:
            if f1 == 0:
                if f == 0:
                    content = content + line + '\n'
                else:
                    head = head + line + '\n'
    
    if f != 0 or fail:
        logging.warning(f'Unclosed parentheses or error usage comment in {filePath}')
    
    if head != '':
        begin = '---'
        heads = f'\n{begin}\n{head}\n{begin}\n'
    else:
        heads = ''
    codes = f'\n```{codeType}\n{content}\n```\n'
    return heads + codes
    pass

def WriteContent(content :str, outputFd :io.TextIOWrapper):
    outputFd.write(content)
    outputFd.write('\n')
    pass

def AddOutlineToOutputFile(level :int, outline :str, outputFd :io.TextIOWrapper):
    prefix = '#' * level + ' '
    outputFd.write(F'{prefix}{outline}\n')
    pass

def AddTemplateToOutputFile(level :int, filePath :str, fileName :str, outputFd :io.TextIOWrapper, profile :json):
    fileType = None
    fileContent = None
    supportLans = profile['support_language']
    
    for suffix, lang in supportLans.items():
        if fileName.endswith(suffix):
            fileType = lang
            curSuffix = suffix
            break
    fileName = fileName[:-len(curSuffix)]
    fileName = fileName.lstrip('0123456789.')
    if fileType == None:
        logging.warn(f'Mate file name to suffix failed.\nFile name: {fileName}\nSupport lang: {supportLans}\n')
        return
    try:
        with open(file=filePath, mode='r') as f:
            fileContent = f.read()
    except BaseException as e:
        logging.error(f'Fail to read file {filePath}, reason: '+e)
        fileContent = None
    if fileContent != None:
        AddOutlineToOutputFile(level=level, outline=fileName, outputFd=outputFd)
        content = AnalysisCode(fileContent=fileContent, codeType=fileType, filePath=filePath, profile=profile)
        WriteContent(content=content, outputFd=outputFd)
    pass

def AddTextToOutputFile(level :int, filePath :str, fileName :str, outputFd :io.TextIOWrapper):
    fileContent = None

    supportLans = profile['support_text_format']
    
    for suffix in supportLans:
        if fileName.endswith(suffix):
            curSuffix = suffix
            break
    fileName = fileName[:-len(curSuffix)]
    
    try:
        with open(file=filePath, mode='r') as f:
            fileContent = f.read()
    except BaseException as e:
        logging.error(f'Fail to read file {filePath}, reason: '+e)
        fileContent = None
    if fileContent != None:
        AddOutlineToOutputFile(level=level, outline=fileName, outputFd=outputFd)
        WriteContent(content=fileContent, outputFd=outputFd)
    pass

def QuarySrcFile(level :int, path :str, profile :json, outputFd :io.TextIOWrapper):
    logging.debug(f'Quarying src dir {path}')
    items = os.listdir(path)
    items.sort(key=srcCmp)

    supportTextSuffix = tuple(profile['support_text_format'])
    supportCodeSuffix = tuple(profile['support_language'].keys())

    # 如果是空文件夹
    if len(items) == 0 and profile['ignore_empty_dir']:
        logging.debug(f'Empty dir{path}, ignore')
        return
    for item in items:
        item_path = os.path.join(path, item)
        # 判断是文件还是文件夹
        if os.path.isfile(item_path):
            logging.debug(f'Path {path} is file')
            if not item in profile['exclude_files']:
                if item.endswith(supportCodeSuffix):
                    logging.debug(f'Path {path} considered to be code')
                    AddTemplateToOutputFile(filePath= item_path, level= level+1, fileName= item, profile=profile, outputFd=outputFd)
                elif item.endswith(supportTextSuffix):
                    logging.debug(f'Path {path} considered to be text')
                    AddTextToOutputFile(filePath= item_path, level= level+1, fileName= item, outputFd=outputFd)

        elif os.path.isdir(item_path):
            if not item in profile['exclude_folders']:
                logging.debug(f'Path {path} is dir')
                AddOutlineToOutputFile(level=level+1, outline=item.lstrip('0123456789.'), outputFd=outputFd)
                QuarySrcFile(level=level+1, path=item_path, profile=profile, outputFd=outputFd)
    pass

def Generate(srcPath :str, profile :json):
    with open(profile['output_file'], 'w') as f:
        QuarySrcFile(level=0,path=srcPath,profile=profile,outputFd=f)
    pass

if __name__ == '__main__':
    # 配置日志记录
    # logging.basicConfig(filename='myapp.log', level=logging.DEBUG, format='%(asctime)s [%(levelname)s] %(message)s')
    logging.basicConfig(level=logging.DEBUG, format='%(asctime)s [%(levelname)s] %(message)s')
    conf_path = './config.json'
    conf_path = os.path.abspath(conf_path)
    if os.path.exists(conf_path):
        logging.info(f'Config file {conf_path} is finded.')
    else:
        logging.warning(f'Config file {conf_path} is not finded.')
        flag = input(f'Do you want to create config file {conf_path}?(Y/n)')
        if flag == 'n':
            logging.error(f'Fail to read {conf_path},exited')
            exit(-1)
        else:
            with open(conf_path, 'w') as conf:
                conf.write(enmptyConf)
            logging.info(f'Please complete the config file {conf_path}')
            exit(0)
    profile = None
    try:
        with open(conf_path, 'r') as config:
            profile = config.read()
    except BaseException as e:
        logging.error('Fail to read file:'+e)
        pass
    logging.debug(f'Read profile:\n{profile}')
    profile : dict = json.loads(profile)
    fullFlag = True
    for key, val in (json.loads(enmptyConf)).items():
        if not key in profile.keys():
            profile[key] = val
            fullFlag = False
    
    if not fullFlag:
        with open(conf_path,'w',encoding='gbk') as f:
            json.dump(profile,f,indent=4)
        pass

    Generate(srcPath=profile['template_path'],profile=profile)
    pass