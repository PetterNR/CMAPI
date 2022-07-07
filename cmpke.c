#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cm-256/nist/rng.h"
#include "cm-256/crypto_kem.h"
#include "cm-256/crypto_kem_mceliece6960119f.h"
#include "cm-256/encrypt.h"
#include "cm-256/operations.h"
#include "cm-256/decrypt.h"
#include "cm-256/params.h"
#include "cm-256/crypto_hash.h"


static PyObject *cm_keypair(PyObject* self, PyObject* args){
    unsigned char *seed;
    Py_ssize_t seed_size;
    unsigned char pk[crypto_kem_PUBLICKEYBYTES];
    unsigned char sk[crypto_kem_SECRETKEYBYTES];
    if (!PyArg_ParseTuple(args, "y#", &seed, &seed_size))
        return NULL;
    
    randombytes_init(seed,0,0);
    crypto_kem_keypair(pk,sk);
    return Py_BuildValue("y#y#", pk,  crypto_kem_PUBLICKEYBYTES, sk, crypto_kem_SECRETKEYBYTES);
}


static PyObject *cm_encrypt(PyObject* self, PyObject* args){
    unsigned char *pk;
    unsigned char key[32];
    unsigned char c[crypto_kem_CIPHERTEXTBYTES];
    Py_ssize_t pk_size,two_e_size;
    if (!PyArg_ParseTuple(args, "y#", &pk, &pk_size))
        return NULL;
    crypto_kem_enc(c, key, pk);
    return Py_BuildValue("y#y#", c,  crypto_kem_CIPHERTEXTBYTES, key, 32);
}

static PyObject *cm_decrypt(PyObject* self, PyObject* args){
    unsigned char *sk;
    unsigned char *c;
    unsigned char key[32];
    Py_ssize_t sk_size, c_size;

    if (!PyArg_ParseTuple(args, "y#y#", &sk, &sk_size ,&c, &c_size))
        return NULL;
    
    crypto_kem_dec(key, c ,sk);
    return Py_BuildValue("y#", key, 32);
}

static PyObject *cm_gen_e(PyObject* self, PyObject* args){
    unsigned char *seed;
    unsigned char two_e[ 1 + SYS_N/8 ] = {2};
	unsigned char *e = two_e + 1;
    Py_ssize_t seed_size;

    if (!PyArg_ParseTuple(args, "y#", &seed, &seed_size))
        return NULL;
    randombytes_init(seed,0,0);
    gen_e(e);
    return Py_BuildValue("y#", two_e, 1+SYS_N/8);
}

static PyObject *hash32B(PyObject* self, PyObject* args){
    unsigned char *input;
    Py_ssize_t input_size;
    unsigned char hash[32];
    if (!PyArg_ParseTuple(args, "y#", &input, &input_size))
        return NULL;
    crypto_hash_32b(hash, input, input_size);
    return Py_BuildValue("y#", hash, 32);
}



static PyMethodDef cmMethods[] = {
    {"keypair", (PyCFunction)cm_keypair, METH_VARARGS, "generates keys for CM"},
    {"encrypt", (PyCFunction)cm_encrypt, METH_VARARGS, "enc"},
    {"decrypt", (PyCFunction)cm_decrypt, METH_VARARGS, "dec"},
    {"hash", (PyCFunction)hash32B, METH_VARARGS, "dec"},
    {"gen_e", (PyCFunction)cm_gen_e, METH_VARARGS, "generate random plaintext"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef cmapi_def = {
    PyModuleDef_HEAD_INIT,
    "cmapi",
    "Some function i guess",
    -1,
    cmMethods
};

PyMODINIT_FUNC PyInit_cmapi(void){
    return PyModule_Create(&cmapi_def);
}