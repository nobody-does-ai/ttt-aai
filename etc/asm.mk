
$(asm/obj): %.S.oo: %.S etc/asmflags
	$(CXX) -o $@ $< @etc/asmflags -c

$(asm/tst) $(asm/exe): %: %.S.oo etc/ld_flags $(lib/lib)
	$(CXX) -o $@ -Wl,--start-group $< $(lib/lib) @etc/ld_flags -Wl,--end-group
