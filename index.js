const rdrand_addon = require('./build/Release/rdrand');
if (typeof rdrand_addon.rdrand_not_supported !== "undefined") {
    throw new Error("RDRAND is not supported on this CPU");
}

module.exports = rdrand_addon;