# rdrand-windows
## RDRAND bindings for Windows

This is a Node.js binding to Intel's hardware random number generator for Ivy Bridge (and later) CPUs, RDRAND. The reason that this package is only available for Windows is because I couldn't care enough to implement cross-compiler support checking for RDRAND.

# Usage examples

Get some random bytes:
```js
const rdrand = require("rdrand-windows");
const randomBytes = rdrand.rdrandBytes(32);
// do something with the random bytes
```

Get some random bytes to use a seed:
```js
const rdrand = require("rdrand-windows");
const seed = rdrand.rdseedBytes(20);
// seed your (cs)prng of choice
```

Get some random numbers

```js
const rdrand = require("rdrand-windows");

const random_32_bit_number = rdrand.rand32();
const random_53_bit_number = rdrand.rand53();
```

# API

```js
rand32(void): number
```
Returns a 32-bit random number.

```js
rand53(void): number
```
Returns a 53-bit random number (up to `Number.MAX_SAFE_INTEGER`).

```js
seed32(void): number
```
Returns a 32-bit random ***seed***. This doesn't go through a CSPRNG, you should only use it to seed your own random number generator.

```js
seed53(void): number
```
Returns a 53-bit random ***seed*** (up to `Number.MAX_SAFE_INTEGER`). This doesn't go through a CSPRNG, you should only use it to seed your own random number generator.

```js
rand64s(void): string
```
Returns a 64-bit random number in string representation.

```js
seed64s(void): string
```
Returns a 64-bit random ***seed*** in string representation. This doesn't go through a CSPRNG, you should only use it to seed your own random number generator.

```js
rdrandBytes(length: number): Buffer
```
Returns a Buffer of the provided length filled with random bytes.

```js
rdseedBytes(length: number): Buffer
```
Returns a Buffer of the provided length filled with random bytes from a seed. This doesn't go through a CSPRNG, you should only use it to seed your own random number generator.

# License
```
MIT License

Copyright (c) 2023 rfl890

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```