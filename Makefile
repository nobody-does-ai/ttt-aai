all:
ifeq ($(MAKE),remake)
include etc/vars.mk
etc/multi.mk etc/cxxflags etc/ld_flags etc/cppflags etc/asmflags:;
all: lib bin tst

test: all

lib/lib:=lib/libutil.aa

show= $(warning $1: $($1))

c++/src:=$(wildcard */*.cc)
c++/obj:=$(c++/src:.cc=.cc.oo)
lib/lst:=$(sort $(dir $(filter-out tst/% bin/%,$(c++/src))))
#    $(warning lib/lst=$(lib/lst))
c++/lib:=$(filter-out bin/%,$(c++/obj))

c++/asm:=$(c++/src:.cc=.cc.SS)
c++/cpp:=$(c++/src:.cc=.cc.ii)
c++/dep:=$(c++/src:.cc=.cc.dd)
c++/exe:=$(filter bin/% tst/%,$(c++/src:.cc=))
c++/tst:=$(filter tst/%,$(c++/obj:.cc.oo=))
c++/abi:=$(filter abi/%,$(c++/obj))

all: $(c++/exe) $(asm/exe)

extra:=$(filter-out $(c++/dep),$(wildcard */*.dd))
$(if $(extra),$(foreach e,$(extra),$(warning extra:$e)))
$(if $(extra),$(foreach e,$(extra),$(shell rm -f $e)))
missing:=$(filter-out $(c++/dep),$(c++/src:.cc=.cc.dd))
$(if $(missing),$(foreach e,$(missing),$(warning missing:$e)))
$(if $(missing),$(foreach e,$(missing),$(eval $e:FORCE)))
include /dev/null $(wildard $(c++/dep))

asm/src:=$(wildcard */*.S)
asm/obj:=$(asm/src:.S=.S.oo)
asm/lib:=$(filter lib/%,$(asm/obj))
asm/exe:=$(filter bin/%,$(asm/src:.S=))
asm/abi:=$(filter abi/%,$(asm/obj))
$(c++/exe) $(asm/exe): $(lib/lib)


all_deps:=$(wildcard */*.dd)
c++_deps:=$(foreach s,$(wildcard */*.cc),$(wildcard $s.dd)))
oth_deps:=$(filter-out $(c++_deps),$(all_deps))

all: $(c++/exe) $(asm/exe) $(lib/lib) 

obj: $(c++/obj) $(asm/obj) 
lib: $(lib/lib) $(lib/lsc) $(abi/lib)

all/obj:= $(c++/obj) $(asm/obj)

all/exe:=$(c++/exe) $(c++/tst) $(asm/exe)
#    
all: $(all/exe)

FORCE:

.PHONY: FORCE

include etc/multi.mk

all: $(c++/obj)


T:=

all:
	@echo made all
	@cp .gitignore .gitignore.old
	@printf '%s\n' $(all/exe) | sort .gitignore -u -o .gitignore -
	@report cmp -s .gitignore .gitignore.old || echo ".gitignore changed"
else
$(shell remake $(MAKECMDGOALS) >&2)
endif
