# gr-ldpc-toolbox

gr-ldpc-toolbox is a GNU Radio out-of-tree module containing a LDPC encoder and
decoder blocks using the ldpc-toolbox Rust library.

## Examples

The `example/ldpc_simulation.grc` flowgraph contains a simulation of encoding
and decoding with the CCSDS r=1/2 k=1024 LDPC code in a BPSK AWGN channel.

## Using Rust in a GNU Radio out-of-tree module

The Rust library is built as a static library with a C API using CMake and
[corrosion](https://github.com/corrosion-rs/corrosion), so that the code ends up
as part of the GNU Radio dynamic library for gr-ldpc-toolbox. The GNU Radio
blocks are simple wrappers that call the C API of ldpc-toolbox.
