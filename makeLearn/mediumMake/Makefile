CC := gcc
subdir := main common module
APP := px4
MODULE :=$(patsubst %,%.a,$(subdir))

all : $(subdir)
	cd build ;  $(CC) -o $(APP) -Xlinker "-(" $(MODULE) -Xlinker "-)" $(LFLAGS)

$(subdir):
	cd $@ && make

.PHONY: $(subdir)
