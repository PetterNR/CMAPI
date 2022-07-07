from curses import KEY_B2
from random import random
from resource import RUSAGE_CHILDREN
import pyaes as AES
import cmapi
import os

# initialization of random MUST be 44 bytes long
def random_seed():
    return os.urandom(44)

# functions example 
# key generation
Pk, Sk = cmapi.keypair(random_seed())
e = cmapi.gen_e(random_seed()) # needs to be the same for encryptions (TreeKEM)

# encrypt / decrypt
c, k = cmapi.encrypt(Pk)
k2 = cmapi.decrypt(Sk,c)
assert k == k2


# included 32 byte hash (256 bit)
someHash = cmapi.hash(b'random variable length input')


for i in range(1):
    # Parent keys
    parentPk, parentSk = cmapi.keypair(random_seed())
    
    # secret error vector to encrypt
    e = cmapi.gen_e(random_seed())
    
    # Child keys:
    LChildPk, LChildSk = cmapi.keypair(random_seed())    
    RChildPk, RChildSk = cmapi.keypair(random_seed())
    
    Lc1, Lk = cmapi.encrypt(LChildPk)
    Rc1, Rk = cmapi.encrypt(RChildPk)
    
    assert Lk != Rk, "keys are the same"
    
    Liv = os.urandom(16)
    Lcounter = AES.Counter(int.from_bytes(Liv,"big"))
    Riv = os.urandom(16)
    Rcounter = AES.Counter(int.from_bytes(Riv,"big"))
    Lcipher = AES.AESModeOfOperationCTR(Lk, Lcounter)
    Rcipher = AES.AESModeOfOperationCTR(Rk, Rcounter)
    
    Lc2 = Lcipher.encrypt(parentSk)
    Rc2 = Rcipher.encrypt(parentSk)
    
    # construct cipher texts
    Lc = (Lc1, Liv, Lc2)
    Rc = (Rc1, Riv, Rc2)
    
    # decrypt Sk for Left
    c1, iv, c2 = Lc
    k = cmapi.decrypt(LChildSk, c1)
    counter = AES.Counter(int.from_bytes(iv,"big"))
    cipher = AES.AESModeOfOperationCTR(k, counter)
    LParentSk = cipher.decrypt(c2)
    assert LParentSk == parentSk
    
    # decrypt Sk for Left
    c1, iv, c2 = Rc
    k = cmapi.decrypt(RChildSk, c1)
    counter = AES.Counter(int.from_bytes(iv,"big"))
    cipher = AES.AESModeOfOperationCTR(k, counter)
    RparentSk = cipher.decrypt(c2)
    assert RparentSk == parentSk
    
    
    

