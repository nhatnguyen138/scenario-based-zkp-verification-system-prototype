# scenario-based-zkp-verification-system-prototype

The following prototype is the proposed design of a scenario-based Zero-Knowledge Proof (ZKP) verification system which allows users (provers) to prove their identity by choosing the information type based on each scenario.

### 1. Introduction

Zero-Knowledge Proof (ZKP) is the concept that allows an entity (prover) to prove its identity without revealing any of its information. Due to the recent popularity of cryptocurrency, ZKP was brought back as zkSNARK (stands for Zero-Knowledge Succinct Non-interactive ARgument of Knowledge) in order to help users protect their data privacy and to prevent the information disclosure. Many SNARK systems, as the result, was developed for this purpose.

The difference between this new system among others is that: although they all use the same framework within the Libsnark library [[1]](https://github.com/scipr-lab/libsnark), only the neccessary information will be chosen to prove the prover's identity in the process. For example, to prove that you are old enough to buy alcohols you only need to show your date of birth to the retailer. In order provide services, the service provider (verifier) requires user (prover)'s authentication. A type of information is asked by the verifier (ie. prover's date of birth); the prover then input that information to the SNARK system to prove their identity.

The prototype consists of 3 types of SNARK verification: age verification (check if the prover meets the age requirement), address verification (check if the prover's house has a service covered by the service provider), and phone number verification (check prover's identity, assuming a phone number is only owned by one person). However, it is worth noting that the prototype is not complete: in the address verification, to truly prove that the address is covered by the service provider, that service provider has to store the list of hashb-based signatures from multiple addresses and whenever it verifies it must check the if the signature is match to the database. By not having a pseudo-database to test this, it is marked as incomplete.

### 2. Build Instructions
``` Linux
$ sudo apt-get install build-essential cmake git libgmp3-dev python-markdown libboost-all-dev libssl-dev
```

### 3. Conclusion
Something else here
