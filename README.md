### vcpkg build with custom triplet for Intel compiler
1. Copy `x64-windows-static.cmake` from `$VCPKG_ROOT/triplets` to `x64-windows-intel-static.cmake`
2. Append below line
```cmake
set(VS_PLATFORM_TOOLSET "Intel C++ Compiler 2023") # Intel icx 2023.x
```
3. install packages
```
vcpkg install --clean-after-build --triplet x64-windows-intel-static boost exprtk if97 fmt metis spdlog nlohmann-json
```
4. export for offline environment
```
vcpkg export --zip -x-all-installed
```

### Build **Boost 1.78**
```
using clang-win : 16 : "C:/Program Files (x86)/Intel/oneAPI/compiler/latest/windows/bin/icx.exe" ;
```

```
b2.exe install --without-python --without-graph_parallel --without-mpi toolset=clang-win variant=debug,release link=static address-model=64 architecture=x86 runtime-link=static threading=multi cxxstd=20
```
