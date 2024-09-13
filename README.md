ACM代码模板

---

src文件下的文件夹和文件是模板

使用方式:
修改config.json文件后, 在终端运行以下命令:
``` shell
make clean
make
```

如果你想将自己的代码打包为PDF, 那么请按照以下步骤执行:
1. 克隆new-template分支:
``` shell
git clone --branch new-template https://github.com/RainbowXXX/AcmTemplate.git
```

2. 新建一个src文件夹
``` shell
mkdir src
```

3. 将需要打包的文件放入文件夹

4. 编辑目录下的config.json文件(如果需要参考以下的文本, 请将注释删除)
``` json
{
    "template_path": "./src/",      // 需要打包的目录
    "exclude_files": [              // 排除项
        "markdown.md"
    ],
    "exclude_folders": [            // 排除文件夹
        ".git",
        "Todo",
        "8.others"
    ],
    "comment_ignore_end": "</ignore>",          // 夹在这两个标记之间的行将被省略(仅对以下声明的代码文件有效)
    "comment_ignore_begin": "<ignore>",
    "comment_marking_end": "</genHead>",        // 夹在这两个标记之间的行将被当做说明放在头部(仅对以下声明的代码文件有效)
    "comment_marking_begin": "<genHead>",
    "support_text_format": [                    // 文本格式文件的后缀
        ".txt",
        ".md"
    ],
    "support_language": {                       // 代码文件后缀与代码语言的对应
        ".cpp": "c++",
        ".h": "c++",
        ".py": "python",
        ".conf": ""
    },
    "ignore_empty_dir": true,                   // 如果是true, 将忽略空文件夹
    "gen_directory": false,                     // 如果是true, 将会生成目录
    "enable_pagination": true,                  // 如果是true, 将会根据module_paging项中的正则表达式决定分页, 如果正则表达式能够匹配描述字符串, 那么这一个标题对应的块将会对 页对齐
    // 描述字符串的格式为 'item_type:{item_type}|level:{level}|outline:{pre_fix +" "+ fileName}|file_path:{filePath}' 以下的正则表达式的意思是 让1级块页对齐
    "module_paging": "^item_type:\\s*(?P<item_type>[^|]+)\\|\\s*level:\\s*(?P<level>1)\\|\\s*outline:\\s*(?P<outline>[^|]+)\\|\\s*file_path:\\s*(?P<file_path>.+)$"
}
```

5. 运行make命令来生成打包文件
``` shell
make
```