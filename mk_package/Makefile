.PHONY: all clean depend

all: brscan

brscan: \
../backend_brscan/.libs/libsane-brother.so.1.0.7 \
../libbrscandec/libbrscandec.so.1.0.0 \
../libbrcolm/libbrcolm.so.1.0.1 \
./Brsane.ini \
./brsanenetdevice.cfg \
../netconfig/brsaneconfig \
../libbrcolm/GrayCmData/BHL/* \
../libbrcolm/GrayCmData/BHL2/* \
../libbrcolm/GrayCmData/BHL2FB/* \
../libbrcolm/GrayCmData/BHLFB/* \
../libbrcolm/GrayCmData/BHMFB/* \
../libbrcolm/GrayCmData/BHminiFB/* \
../libbrcolm/GrayCmData/YL4/* \
../libbrcolm/GrayCmData/YL4FB/* \
../libbrcolm/GrayCmData/ZL2/* \
../libbrcolm/GrayCmData/ZL2FB/* \
../libbrcolm/GrayCmData/ZLe/* \
../libbrcolm/GrayCmData/ZLeFB/* \
./brscan.list \
./setupSaneScan
	rm -rf brscan
	mkdir brscan
	sh makepackage
	mkdir -p ../RELEASE
	cp -p linux-4.4-x86_64/brscan-0.2.4-1-linux-4.4-x86_64.rpm \
		../RELEASE/brscan-0.2.4-1-x86_64.rpm


clean:
	rm -fR linux-4.4-x86_64
	rm -fR brscan

brscand:
	sh makepackage
# DO NOT DELETE
