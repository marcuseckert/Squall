SLInterface = {};

(function () {

    SLInterface.getValue = null;
    SLInterface.findMemberAtNumer = null;
    SLInterface.findKey = null;
    SLInterface.findThisLayer = null;
    SLInterface.findProperty = null;
    SLInterface.findLayer = null;
    SLInterface.findComposition = null;
    SLInterface.getBaseCaller = null;
    SLInterface.parentReference = null;

    function isNumeric(n) {
        return !isNaN(parseFloat(n)) && isFinite(n);
    }

    var standardGetterSetter = function (baseCaller, parentReference, isKey) {
        return {

            get: function (target, name) {

                if (baseCaller) {
                    parentReference = SLInterface.getBaseCaller(baseCaller);
                }
                var isNum = false;
                try {
                    isNum = isNumeric(name);
                } catch (error) {
                    isNum = false;
                }
 
                if (isNum) {
                    return SLInterface.findMemberAtNumer(name, null, parentReference);
                }
 
                if (typeof name === "symbol") {
                    return null;
                } else if (name == "pRef") {
                    return parentReference;
                }
                else if (name == "valueOf") {
                    return function () {
                        return SLInterface.getValue(parentReference);
                    };
                }
 
                if (name == "isProxy") {
                    return true;
                }

                if (name == "value") {
                    return SLInterface.getValue(parentReference);
                }

                if (isKey) {
                    return SLInterface.findKey(name, null, parentReference);
                } else {
                    return SLInterface.findProperty(name, null, parentReference);
                }

            },

            set: function (target, name, value) {

            }
        }
    };

    SLInterface.createPropertyProxy = function (baseCaller) {

        var getProx = function (parent) {
            var p = new Proxy(function (name) {
                return SLInterface.findProperty(name, null, parent);
            }, standardGetterSetter(baseCaller, SLInterface.parentReference));
            return p;
        }
        return getProx(SLInterface.parentReference);

    };
    SLInterface.createLayerProxy = function (baseCaller) {
        var p = new Proxy(SLInterface.findLayer, standardGetterSetter(baseCaller, SLInterface.parentReference));
        return p;
    };
    SLInterface.createKeyProxy = function (baseCaller) {
        var p = new Proxy(SLInterface.findKey, standardGetterSetter(baseCaller, SLInterface.parentReference, true));
        return p;
    };
    SLInterface.createThisLayerProxy = function (baseCaller) {
        var p = new Proxy(SLInterface.findThisLayer, standardGetterSetter(baseCaller));
        return p;
    };

} ());
