RM = del

PANDOC = pandoc
PYTHON = python
PFLAGS = --pdf-engine=xelatex --toc -V mainfont="SimSun" -V CJKmainfont="SimSun"

TARGET = output.pdf
INTER_TARGET = .\output.md

GEN = .\NewGenerater.py
CONFIG = .\config.json

${INTER_TARGET}:
	${PYTHON} ${GEN} -f ${CONFIG} -o ${INTER_TARGET} -v

${TARGET}: ${INTER_TARGET}
	${PANDOC} ${INTER_TARGET} -o ${TARGET} ${PFLAGS}

clean:
	${RM} ${INTER_TARGET}
	${RM} ${TARGET}

all: clean ${INTER_TARGET} ${TARGET}

.PHONY: all