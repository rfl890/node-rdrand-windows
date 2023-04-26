const rdrand_addon = require('./build/Release/rdrand');
if (typeof rdrand_addon.rdrand_not_supported !== "undefined") {
    throw new Error("RDRAND is not supported on this CPU");
}
function rdrandBytes(length) {
    if (length === 8) {
        return rdrand_addon.rand64b();
    }
    if (length <= 8) {
        return rdrand_addon.rand64b().slice(0, length);
    }
    const rands = []; // random bytes
    const overflow = length % 8;
    const eights = (length - overflow) / 8; /* how many groups of 8 bytes */
    if (overflow == 0) /* divisible by 8 */ {
        for (let i = 0; i < eights; i++) {
            rands.push(rdrand_addon.rand64b());
        }
        return Buffer.concat(rands);
    }
    for (let i = 0; i < eights; i++) {
        rands.push(rdrand_addon.rand64b());
    }
    rands.push(rdrand_addon.rand64b().slice(0, overflow));
    return Buffer.concat(rands);
}
function rdseedBytes(length) {
    if (length === 8) {
        return rdrand_addon.seed64b();
    }
    if (length <= 8) {
        return rdrand_addon.seed64b().slice(0, length);
    }
    const rands = []; // random bytes
    const overflow = length % 8;
    const eights = (length - overflow) / 8; /* how many groups of 8 bytes */
    if (overflow == 0) /* divisible by 8 */ {
        for (let i = 0; i < eights; i++) {
            rands.push(rdrand_addon.seed64b());
        }
        return Buffer.concat(rands);
    }
    for (let i = 0; i < eights; i++) {
        rands.push(rdrand_addon.seed64b());
    }
    rands.push(rdrand_addon.seed64b().slice(0, overflow));
    return Buffer.concat(rands);
}
module.exports = {
    rand32: rdrand_addon.rand32,
    rand53: rdrand_addon.rand53,
    seed32: rdrand_addon.seed32,
    seed53: rdrand_addon.seed53,
    rand64s: rdrand_addon.rand64s,
    seed64s: rdrand_addon.seed64s,
    rdrandBytes,
    rdseedBytes
}