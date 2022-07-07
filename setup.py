from distutils.core import setup, Extension
cmfolder = "cm-256/"

so = ["nist/rng.c",
    "benes.c",
    "bm.c",
    "controlbits.c",
    "decrypt.c",
    "encrypt.c",
    "gf.c",
    "operations.c",
    "pk_gen.c",
    "root.c",
    "util.c",
    "sk_gen.c",
    "synd.c",
    "transpose.c",]
for i in range(len(so)):
    so[i] = cmfolder + so[i]
so.append("cmpke.c")

cmapi = Extension("cmapi", sources=so, include_dirs=["/home/proneid/Documents/CM_py"],
                       libraries=["keccak",
                                  "crypto",
                                  "dl"],
                       runtime_library_dirs=["/usr/lib"],
                       extra_compile_args=["-DCRYPTO_NAMESPACE(x)=x", "-D_CRYPTO_NAMESPACE(x)=_##x"])
setup(name="cmapiPackage", version ="1.0", description="stuff",ext_modules=[cmapi])