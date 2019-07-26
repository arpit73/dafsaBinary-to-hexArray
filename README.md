### Introduction

[make_dafsa.py](https://searchfox.org/mozilla-central/source/xpcom/ds/tools/make_dafsa.py) in conjunction with [prepare_tlds.py](https://searchfox.org/mozilla-central/source/netwerk/dns/prepare_tlds.py) is used to generate a [C++ hex array](https://searchfox.org/mozilla-central/source/__GENERATED__/netwerk/dns/etld_data.inc) when running in firefox build system and a binary file when running with remote-settings-lambdas server.

This project aims to use the generated binary file to reverse the packing and generate a C++ array of hexadecimal numbers.

#### How to run

Clone this repository.

###### Compile

```bash
$ g++ convert.cpp -o convert
```

###### Execute

```bash
$ ./convert input.bin output.inc
```

#### Files

```
.
├── convert        // The compiled binary of convert.cpp
├── convert.cpp    // The C++ file to be that is compiled
├── data.py        // I used this while writing the code to reference logic and check that the integers being generated were identical.
├── input.bin      // The input binary file, as created by use of --bin flag in prepare_tlds.py
├── output.inc     // The output file generated with convert.cpp, to compared agaims sample.inc
└── sample.inc     // The output of words_to_cxx when running prepare_tlds.py with no flag, used as reference for judging the correctness of output.inc
```

#### Overview of the code

-   The binary is read to be stored inside a vector of length set to the the number of packed elements inside the binary.
-   The vector is converted into another vector of `unsigned integers` that has data identical to what is seen before conversion in make_dafsa.py
-   This vector is finally converted to hexadecimal numbers(with at least two digits) and formatted to follow correct syntax and incorporate so information.

#### Conclusion

The convert.cpp produces the correct output as can be verified by by comaparing [output.inc](./output.inc) with [etld_data.inc](https://searchfox.org/mozilla-central/source/__GENERATED__/netwerk/dns/etld_data.inc), they are nearly identical.
