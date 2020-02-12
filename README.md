# scenario-based-zkp-verification-system-prototype

The following prototype is the proposed design of a scenario-based Zero-Knowledge Proof (ZKP) verification system which allows users (provers) to prove their identity by choosing the information type based on each scenario.

### 1. Introduction

Zero-Knowledge Proof (ZKP) is the concept that allows an entity (prover) to prove its identity without revealing any of its information. Due to the recent popularity of cryptocurrency, ZKP was brought back as zkSNARK (stands for Zero-Knowledge Succinct Non-interactive ARgument of Knowledge) in order to help users protect their data privacy and to prevent the information disclosure. Many SNARK systems, as the result, was developed for this purpose.

The difference between this new system among others is that: although they all use the same framework within the Libsnark library [[1]](https://github.com/scipr-lab/libsnark), only the neccessary information will be chosen to prove the prover's identity in the process. For example, to prove that you are old enough to buy alcohols you only need to show your date of birth to the retailer. In order provide services, the service provider (verifier) requires user (prover)'s authentication. A type of information is asked by the verifier (ie. prover's date of birth); the prover then input that information to the SNARK system to prove their identity.

The prototype consists of 3 types of SNARK verification: age verification (check if the prover meets the age requirement), address verification (check if the prover's house has a service covered by the service provider), and phone number verification (check prover's identity, assuming a phone number is only owned by one person). However, it is worth noting that the prototype is not complete: in the address verification, to truly prove that the address is covered by the service provider, that service provider has to store the list of hashb-based signatures from multiple addresses and whenever it verifies it must check the if the signature is match to the database. By not having a pseudo-database to test this, it is marked as incomplete.

### 2. Build Instructions

The following is the prototype's build instructions on Linux OS. According to SCIPR Lab annotation in the Libsnark library [[1]](https://github.com/scipr-lab/libsnark), due to some limitation in the library's portability, it is recommended to run the implementation within the setups that they have already tested so far. The prototype is implemented on 'Ubuntu 16.04 LTS'. After downloading the source code of the system prototype, do the following:

Installing the requisite packages - Ubuntu 16.04 LTS:
``` Linux
$ sudo apt-get install build-essential cmake git libgmp3-dev python-markdown libboost-all-dev libssl-dev
```

Go to the <b>depends</b> folder and get a Git submodule of the Libsnark library in the folder 'libsnark':
``` Linux
$ cd depends
$ git submodule add https://github.com/scipr-lab/libsnark.git libsnark
```
(<b>Note</b>: if the git package is not running, type in: ```Linux git init```)

Fetch all the dependencies from the Libsnark Github repository:
``` Linux
$ git submodule update --init --recursive
```
(<b>Note</b>: it is recommended that the system is updated before updating the submodule; otherwise, some errors will occur). 

Make a build directory, compile and run the prototype:
``` Linux
$ cd ..
$ mkdir build && cd build && cmake ..
$ make
$ ./src/main
```

When running the prototype, you will be asked to choose the type of SNARK verification, either age, address or phone number verification. All the processes will be run within the prototype; however, in real-life scenario there will be at least 3 entitities: generator (generates public and private keys for verification), prover (creates proof from the keys and the information), verifier (uses the proof as well as the public credentials to verify the user's proof).

### 3. Conclusion

In short, the prototype allows the provers to choose only the required information for the verification, protects th0em from unnecessary information disclosure. Although the prototype design has not been fully developed as well as it is fairly simple, it uses the concepts as well as the technologies needed for the future work and development (ie. SHA256 compression function and hash-based signatures).
