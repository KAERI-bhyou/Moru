Build **Boost 1.78**

```
using clang-win : 16 : "C:/Program Files (x86)/Intel/oneAPI/compiler/latest/windows/bin/icx.exe" ;
```

```
b2.exe install --without-python --without-graph_parallel --without-mpi toolset=clang-win variant=debug,release link=static address-model=64 architecture=x86 runtime-link=static threading=multi cxxstd=20
```


vcpkg
```
vcpkg install --clean-after-build --triplet x64-windows-static exprtk if97 fmt metis  spdlog nlohmann-json
```