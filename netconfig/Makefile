.PHONY: all clean depend

all: brsaneconfig

brscan: brsaneconfig

brsaneconfig: brsaneconfig.c ../backend_src/brother_advini.c ../backend_src/brother_advini.h resource.h
	sh mk_brsaneconfig

clean:
	rm -f brsaneconfig

depend:
	makedepend brsaneconfig.c ../backend_src/brother_advini.c
