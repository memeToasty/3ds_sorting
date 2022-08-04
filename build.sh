# I know this is very illegal, because there is already a Makefile, but I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.
# I don't know how to make it work.

bannertool makebanner -ci meta/COMMON.cgfx -a meta/beep.wav -o meta/banner.bnr
makerom -f cia -o 3ds_sorting.cia -banner meta/banner.bnr -elf ./3ds_sorting.elf -rsf meta/rominfo.rsf -icon meta/icon.icn
