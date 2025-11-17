
$(asm/obj): %.S.oo: %.S etc/asmflags
	as -o $@ $< @etc/asmflags

$(c++/obj): %.cc.oo: %.cc  etc/cxxflags etc/cppflags
	$(CXX)  -o $@ -c $< @etc/cxxflags @etc/cppflags

