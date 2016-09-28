function SLRandomNumberGenerator() {
    this.seed = 0;
    this.baseSeed = 0;
    this.useTime = true;
    var SLm = 139968;
    var SLa = 3877;
    var SLc = 29573;

    this.random = function (a, b) {
        var t = SLuseTime ? time | 1.0 : 1.0;

        this.seed = ((this.seed * t * SLa + SLc) % SLm);
        var r = res / SLm;

        if (a && !b) {
            return mul(a, r);
        } else if (a && b) {
            return add(a, mul(sub(a, b), r));
        }
        return r;
    }

    this.gaussRandom = function (a, b) {
        var x1, x2, w, y1, y2;

        do {
            x1 = 2.0 * random() - 1.0;
            x2 = 2.0 * random() - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = Math.sqrt((-2.0 * Math.log(w)) / w);
        y1 = x1 * w;
        y2 = x2 * w;
    }

}

var SLRandom = new SLRandomNumberGenerator();

function SLGetValue(v) {
    if (v.isProxy) {
        return v.value;
    }
    return v;
}

function seedRandom(seed, timeless) {
    seed = SLGetValue(seed);
    timeless = SLGetValue(timeless);
    SLRandom.seed = SLRandom.baseSeed + seed;
    SLRandom.useTime = !timeless;
}
function random(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    return SLRandom.random(a, b);
}

function add(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    if (a instanceof Array && b instanceof Array) {
        var maxNum = Math.min(a.length, b.length);
        var rArray = [];
        for (var i = 0; i < maxNum; i++) {
            rArray.push(a[i] + b[i]);
        }
        var biggerArray = a.length > b.length ? a : b;
        for (var i = maxNum; i < biggerArray.length; i++) {
            rArray.push(biggerArray[i]);
        }
        return rArray;
    } else if ((a instanceof Array) && !(b instanceof Array)) {
        var rArray = a.slice();
        rArray[0] = a[0] + b;
        return rArray;
    } else if (!(a instanceof Array) && (b instanceof Array)) {
        var rArray = b.slice();
        rArray[0] = b[0] + a;
        return rArray;
    } else {
        return a + b;
    }
}


function sub(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    if (a instanceof Array && b instanceof Array) {
        var maxNum = Math.min(a.length, b.length);
        var rArray = [];
        for (var i = 0; i < maxNum; i++) {
            rArray.push(a[i] - b[i]);
        }
        var biggerArray = a.length > b.length ? a : b;
        for (var i = maxNum; i < biggerArray.length; i++) {
            if (biggerArray === b) {
                rArray.push(-biggerArray[i]);
            } else {
                rArray.push(biggerArray[i]);
            }
        }
        return rArray;
    } else if ((a instanceof Array) && !(b instanceof Array)) {
        var rArray = a.slice();
        rArray[0] = a[0] - b;
        return rArray;
    } else if (!(a instanceof Array) && (b instanceof Array)) {
        var rArray = b.slice();
        rArray[0] = a - b[0];
        for (var i = 1; i < rArray.length; i++) {
            rArray[i] *= -1.0;
        }
        return rArray;
    } else {
        return a - b;
    }
}


function mul(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    
    if (a instanceof Array) {
        var rArray = [];
        for (var index = 0; index < a.length; index++) {
            rArray.push(a[index] * b);
        }
        return rArray;
    } else {
        return a * b;
    }
}

function div(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    if (a instanceof Array) {
        var rArray = [];
        for (var index = 0; index < a.length; index++) {
            rArray.push(a[index] / b);
        }
        return rArray;
    } else {
        return a / b;
    }
}

function SLClampValue(a, l, l2) {
    if (l>l2) {
        var t = l;
        l = l2;
        l2 = t;
    }
    return Math.min(Math.max(a, l), l2);
}

function SLValueAtIndex(v, index) {
    return v instanceof Array ? index >= v.length ? 0  : v[index] : index > 0 ? 0 : v;
}

function clamp(a, limit, limit2) {
    a = SLGetValue(a);
    limit = SLGetValue(limit);
    limit2 = SLGetValue(limit2);
    var n1 = a instanceof Array ? a.length : 1;
    var n2 = limit instanceof Array ? limit.length : 1;
    var n3 = limit2 instanceof Array ? limit2.length : 1;

    var nums = [n1,n2,n3].sort();
    var max = nums[1];
    if (max > 1) {
        var rArray = new Array(max);
        for (var i = 0; i < max; i++) {
            rArray[i] = SLClampValue(SLValueAtIndex(a, i), SLValueAtIndex(limit, i), SLValueAtIndex(limit2, i));
        }
        return rArray;
    } else {
        return SLClampValue(a, limit, limit2);
    }
}

function dot(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    if (a instanceof Array && b instanceof Array) {
        var maxNum = Math.min(a.length, b.length);
        var n = 0;
        for (var i = 0; i < maxNum; i++) {
            n += a[i] * b[i];
        }
        return n;
    } else if (a instanceof Array && !(b instanceof Array)) {
        return a[0]*b;
    } else  if (!(a instanceof Array) && (b instanceof Array)) {
        return a*b[0];
    } else {
        return a*b;
    }
}

function cross(a, b) {
    a = SLGetValue(a);
    b = SLGetValue(b);
    var b2 = b.length>2 ? b[2] : 0.0;
    var a2 = a.length>2 ? a[2] : 0.0;
    return [a[1] * b2 - a2 * b[1], a2 * b[0] - a[0] * b2, a[0] * b[1] - a[1] * b[0]];
}

function lengthVector(v) {
    v = SLGetValue(v);
    var r = 0;
    for (var i = 0; i < v.length; i++) {
        r += v[i] * v[i];
    }
    if (r == 0) {
        return 0.0;
    } else {
        return Math.sqrt(r);
    }
}

function normalize(v) {
    v = SLGetValue(v);
    
    var l = length(v);
    if (l != 0) {
        return mul(v, 1.0 / l);
    }
    return v;
}

function length(a, b) {
    a = SLGetValue(a);
    if (b){
        b = SLGetValue(b);
    }
    if (b) {
        return length(sub(b, a));
    } else {
        return lengthVector(a);
    }
}

function degreesToRadians(d) {
    d = SLGetValue(d);
    return d * (Math.PI / 180.0);
}

function radiansToDegrees(r) {
    r = SLGetValue(r);
    return r * (180.0 / Math.PI);
}

function lookAt(fromV, to) {
    fromV = SLGetValue(fromV);
    to = SLGetValue(to);
    var v = sub(to, fromV);
    var angle = radiansToDegrees(Math.atan2(v));
    if (angle < 0) {
        angle += 360;
    }
    return angle;
}

