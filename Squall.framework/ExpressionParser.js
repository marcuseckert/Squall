
expressionCorrector = {};
String.prototype.capitalize = function () {
    return this.charAt(0).toUpperCase() + this.slice(1);
};
(function () {

    

    var propertyToFunction = [
        "time",
        "numLayers",
        "width",
        "height",
        "duration",
        "frameDuration",
        "name",
        "source",
        "index",
        "parent",
        "hasParent",
        "inPoint",
        "outPoint",
        "enabled",
        "active",
        "anchorPoint",
        "position",
        "scale",
        "rotation",
        "opacity",
        "timeRemap",
        "orientation",
        "rotationX",
        "rotationY",
        "rotationZ",
        "value",
        "velocity",
        "speed",
        "numKeys",
        "propertyIndex"];
    
     var functionToFunction = [
        "layer",
        "content",
        "propertyGroup"];

    var ExpressionCorrector = function (expression) {
        var mainString = expression;
        var toDefine = [];
        var me = this;
        var correctionMap = {};

        function joinWithOperator(left, right, op) {
            if (op == "+" || op == "+=") {
                return "add(" + left + "," + right + ")";
            } else if (op == "*" || op == "*=") {
                return "mul(" + left + ", " + right + ")";
            } else if (op == "/" || op == "/=") {
                return "div(" + left + "," + right + ")";
            } else if (op == "-" || op == "-=") {
                return "sub(" + left + "," + right + ")";
            } else {
                return left + op + right;
            }

        }

        var openA = 0;

        var finalStrings = [];

        function closeWith(c) {

            if (openA < 0) {
                return;
            }
            //console.log("close ", c);
            if (c > openA) {
                var nString = mainString.substr(openA, c - openA);

                finalStrings.push(nString);
            }
            openA = -1;
        }

        function open(node) {

            if (node.type != "BinaryExpression") {
                if (openA < 0) {
                    //console.log("open ", node.range[0]);
                    openA = node.range[0];
                }
            }
        }

        function getFlatStringForPropertyWithoutAppending(prop) {

            if (Array.isArray(prop)) {
                var s = "";
                for (var i = 0; i < prop.length; i++) {
                    var p = prop[i];
                    s += getFlatStringForPropertyWithoutAppending(p);
                    if (i < prop.length - 1) {
                        s += ",";
                    }
                }
                return s;
            } else {
                closeWith(prop.range[0]);
                var num = finalStrings.length;
                var returnString = "";
                flatten(prop);
                closeWith(prop.range[1]);
                for (var i = num; i < finalStrings.length; i++) {
                    returnString += finalStrings[i];
                }

                while (finalStrings.length > num) {
                    finalStrings.pop();
                }
                return returnString;
            }
        }

        function printProperty(property) {
            var s = mainString.substr(property.range[0], property.range[1] - property.range[0]);
            console.log("s", s);

        }

        function performFlattening(node) {
            open(node);
            for (var property in node) {
                if (property == "handlers") {
                    continue;
                }
                if (node.hasOwnProperty(property) && node[property]) {
                    if (node[property].hasOwnProperty("type")) {
                        flatten(node[property]);

                    } else if (Array.isArray(node[property]) && node[property].length > 0 && node[property][0].hasOwnProperty("type")) {

                        for (var i = 0; i < node[property].length; i++) {
                            var element = node[property][i];
                            flatten(element);
                        }
                    }
                }
            }
        }

        function removeStringAtEnd(string) {

            var lastString = finalStrings[finalStrings.length - 1];
            finalStrings.pop();
            if (lastString != string) {
                var replaceString = lastString.trim();
                replaceString = replaceString.substr(0, replaceString.length - string.length);
                finalStrings.push(replaceString);
            }
        }



        var endStack = [];
        var memberExpressionStack = [];
        function lastMember() {
            return memberExpressionStack[memberExpressionStack.length - 1];
        }
        function pushMember() {
            memberExpressionStack.push({ m: 0, needsEnd: false });
        }
        function NeedsEnd() {
            memberExpressionStack[memberExpressionStack.length - 1].needsEnd = true;
        }
        function WasEnded() {
            memberExpressionStack[memberExpressionStack.length - 1].needsEnd = false;
        }

        function currentMember() {
            return memberExpressionStack[memberExpressionStack.length - 1];
        }

        function popMember() {
            memberExpressionStack.pop();
        }
        function incrementMember() {
            memberExpressionStack[memberExpressionStack.length - 1].m++;
            //console.log("increment", memberExpressionStack[memberExpressionStack.length - 1].m);
        }
        function decrementMember() {
            memberExpressionStack[memberExpressionStack.length - 1].m--;
            //console.log("decrement", memberExpressionStack[memberExpressionStack.length - 1].m);
        }
        function isLastMember() {
            return memberExpressionStack[memberExpressionStack.length - 1].m == 1 && memberExpressionStack[memberExpressionStack.length - 1].needsEnd;
        }

        function forceEndNode(node) {
            var r = ((node.property.name != "name") &&
                (Array.prototype[node.property.name] != undefined
                    || Array[node.property.name] != undefined || String[node.property.name] != undefined || String.prototype[node.property.name] != undefined));

            return r;
        }

        pushMember();

        function flatten(node) {
            
            if (correctionMap[node.type]) {
                correctionMap[node.type](node);
            } else {
                performFlattening(node);
            }
        }

        function processIdentifier(node) {
            if (propertyToFunction.indexOf(node.name) > -1 && toDefine.indexOf(node.name) == -1) {
                toDefine.push(node.name);
            }
            performFlattening(node);
        }

        function processCallExpression(node) {
            incrementMember();

            flatten(node.callee);

            pushMember();
            var p = getFlatStringForPropertyWithoutAppending(node.arguments);
            popMember();

            var suffix = "";

            if (isLastMember()) {
                WasEnded();
                
                suffix = ", { 'end' : true }";
            }
            finalStrings.push(p + suffix);
            decrementMember();

            if (node.arguments.length > 0) {
                openA = node.arguments[node.arguments.length - 1].range[1];
            } else {
                open(node);
            }
        }

        function processMemberExpression(node) {
            incrementMember();

            var convertFunction = propertyToFunction.indexOf(node.property.name) > -1 || functionToFunction.indexOf(node.property.name) > -1;
            if (convertFunction) {
                NeedsEnd();
            }
            flatten(node.object);

            var forceEnd = forceEndNode(node);

            pushMember();

            var p = getFlatStringForPropertyWithoutAppending(node.property);
            popMember();

            var needsEnd = memberExpressionStack[memberExpressionStack.length - 1].needsEnd;

            if (node.property.type == "Literal") {
                p = node.property.value;
            } else if (node.property.type == "Identifier") {
                p = node.property.name;
            }

            if (node.computed) {
                if (needsEnd) {
                    removeStringAtEnd("[");
                    openA = node.property.range[1] + 1;
                } else {
                    openA = node.property.range[1];
                }

            } else {
                if (needsEnd) {
                    removeStringAtEnd(".");
                }
                openA = node.property.range[1];
            }

            var suffix = "";
            if (isLastMember()) {
                WasEnded();
                suffix = ", { 'end' : true }";
            }

            if (forceEnd && currentMember().needsEnd) {
                WasEnded();
                finalStrings.push("('', { 'end' : true })." + p);
            } else if (needsEnd) {
                if (isNaN(p)) {
                    finalStrings.push("('" + p.capitalize() + "'" + suffix + ")");
                } else {
                    finalStrings.push("(" + p + suffix + ")");
                }
            } else {
                finalStrings.push(p);
            }

            decrementMember();
        }

        function processOperator(node) {
            var assigment = node.type == "AssignmentExpression";
            if (assigment && node.operator == "=") {

                performFlattening(node);
            } else {
                closeWith(node.range[0]);

                var leftNum = finalStrings.length;
                var leftString = "";
                flatten(node.left);

                closeWith(node.left.range[1]);
                //closeWith(node.right.range[0]-1);
                for (var i = leftNum; i < finalStrings.length; i++) {
                    leftString += finalStrings[i];
                }

                while (finalStrings.length > leftNum) {
                    finalStrings.pop();
                }

                var rightNum = finalStrings.length;
                var rightString = "";
                flatten(node.right);
                closeWith(node.right.range[1]);

                for (var i = rightNum; i < finalStrings.length; i++) {
                    rightString += finalStrings[i];
                }
                while (finalStrings.length > rightNum) {
                    finalStrings.pop();
                }
                if (assigment) {

                    var f = joinWithOperator(leftString, rightString, node.operator);
                    finalStrings.push(leftString + "=" + f);
                } else {
                    finalStrings.push(joinWithOperator(leftString, rightString, node.operator));
                }

                openA = node.range[1];
            }
        }



        function correctObject(ob) {

            var r = flatten(ob);
            closeWith(ob.range[1]);

            var fString = "";
            for (var i = 0; i < finalStrings.length; i++) {
                var element = finalStrings[i];
                fString += element;
            }
 
            return fString;
        }

        this.correctToCallExpression = function (ob) {
            correctionMap["Identifier"] = processIdentifier;
            correctionMap["CallExpression"] = processCallExpression;
            correctionMap["MemberExpression"] = processMemberExpression;
            correctionMap["BinaryExpression"] = processOperator;
            correctionMap["AssignmentExpression"] = processOperator;
            return correctObject(ob);
        }
        this.correctToProxyExpressionWithDefineables = function (ob, define) {
            if (define) {
                correctionMap["Identifier"] = processIdentifier;
            }
            correctionMap["BinaryExpression"] = processOperator;
            correctionMap["AssignmentExpression"] = processOperator;
 
            return correctObject(ob);
        }

        this.toDefine = toDefine;
    }

    expressionCorrector.correct = function (expression, mode) {
 
        var parsed = esprima.parse(expression, { range: true });
        //console.log(JSON.stringify(ob, null, 4));

        var ob = {};
        var defineables = [];        

        switch (mode) {
            case "call": {
                var e = new ExpressionCorrector(expression);
 
                ob.callExpression = e.correctToCallExpression(parsed);
                defineables = e.toDefine;
            }   break;
            case "proxy": {
                var e2 = new ExpressionCorrector(expression);
                ob.proxyExpression = e2.correctToProxyExpressionWithDefineables(parsed, true);
                defineables = e2.toDefine;
            }
                break;
            case "both": {
                var e = new ExpressionCorrector(expression);
                ob.callExpression = e.correctToCallExpression(parsed);
                defineables = e.toDefine;

                var e2 = new ExpressionCorrector(expression);
                ob.proxyExpression = e2.correctToProxyExpressionWithDefineables(parsed, false);
            }
                break;
            default:
                break;
        }

        if (defineables.length > 0) {
            ob.toDefine = defineables;
        }
        return ob;
    }

} ());

