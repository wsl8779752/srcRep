CC := gcc
DIR_SRC = src
DIR_INC = inc
DIR_COMMON_INC = /home/k/src/srcRep/makeLearn/mediumMake/common/inc
TYPE_SRC = .c
TYPE_INC = .h

CFLAGS := -I$(DIR_INC) -I$(DIR_COMMON_INC)
ifeq ($(DEBUG),true)
CFLAGS += -g
endif


# MODULE = /home/wei/src/srcRep/makeLearn/mediumMake/common
MODULE := $(realpath .)  
# DIR_BUILD =/home/wei/src/srcRep/makeLearn/mediumMake/common 
DIR_BUILD := $(MODULE)
#MODULE = common
MODULE := $(notdir $(MODULE))
#DIR_BUILD = /home/wei/src/srcRep/makeLearn/mediumMake/build
DIR_BUILD := $(patsubst %/$(MODULE),%,$(DIR_BUILD))/build

# 过程文件放在build/common 下
DIR_OUTPUT := $(addprefix $(DIR_BUILD)/, $(MODULE))
# 这个是最终的.a 文件放在 build/ 下

OUTPUT := $(MODULE).a
OUTPUT := $(addprefix $(DIR_BUILD)/, $(OUTPUT))

SRCS := $(wildcard src/*.c)
OBJECTS := $(SRCS:.c=.o)
OBJECTS := $(patsubst src/%, $(DIR_OUTPUT)/%, $(OBJECTS))

vpath %$(TYPE_INC) $(DIR_INC)
vpath %$(TYPE_INC) $(DIR_COMMON_INC)
vpath %$(TYPE_SRC) $(DIR_SRC)

all : $(DIR_OUTPUT) $(OUTPUT)
.PHONY : test all
$(OUTPUT) : $(OBJECTS)
	ar r $@ $^ 

$(DIR_OUTPUT)/%.o : %.c 
	gcc -c $^ -o $@ $(CFLAGS)

$(DIR_OUTPUT):
	@echo "mkdir $(DIR_OUTPUT)"
	$(shell mkdir -p  $(DIR_OUTPUT))

test : 
	@echo "OUTPUT:$(OUTPUT)"
	@echo "DIR_BUILD:$(DIR_BUILD)"
	@echo "DIR_OUTPUT: $(DIR_OUTPUT)"
	@echo "MODULE:$(MODULE)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS:$(OBJECTS)"
