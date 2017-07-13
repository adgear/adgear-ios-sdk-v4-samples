(function() {
 
    var mraidview = window.mraidview = {};
    var listeners = {};
    var nativeCallQueue = [];

    mraidview.addEventListener = function(event, listener) {
        if (listeners[event] == null) {
            listeners[event]=[];
        }
        for (var handler in listeners[event]) {
            if (listener == handler) return;
        }
        listeners[event].push(listener);
    };

    mraidview.removeEventListener = function(event, listener) {
        if (listeners[event]!=null) {
            listeners[event].remove(listener);
        }
    };

    mraidview.fireChangeEvent = function(properties) {
        if (listeners['change']!=null) {
            listeners['change'].forEach(function(listener){
                listener(properties);
            });
        }
    };

    mraidview.fireErrorEvent = function(message, action) {
        if (listeners['error']!=null) {
            listeners['error'].forEach(function(listener){
                listener(message, action);
            });
        }
    };
  
    mraidview.executeNativeCall = function(call) {
        if(window.webkit && window.webkit.messageHandlers && window.webkit.messageHandlers.mraid) {
            window.webkit.messageHandlers.mraid.postMessage(call);
        }
    }
})();

(function() {

    var mraid = window.mraid = {};
    mraid.adgear = {};

    var STATES = mraid.STATES = {
        LOADING: 'loading',
        DEFAULT: 'default',
        EXPANDED: 'expanded',
        RESIZED: 'resized',
        HIDDEN: 'hidden'
    };

    var EVENTS = mraid.EVENTS = {
        ERROR: 'error',
        READY: 'ready',
        SIZECHANGE: 'sizeChange',
        STATECHANGE: 'stateChange',
        VIEWABLECHANGE: 'viewableChange',
        HEADINGCHANGE: 'headingChange',
        TILTCHANGE: 'tiltChange',
        INFO: 'info',
        ORIENTATIONCHANGE: 'orientationChange',
        LOCATIONCHANGE: 'locationChange'
    };

    var state = STATES.LOADING;

    var version = '2.0.';

    var placementType = 'inline';

    var viewable = true;

    var expandProperties = {
        width: -1,
        height: -1,
        useCustomClose: false,
        isModal: true
    };

    var orientationProperties = {
        allowOrientationChange: true,
        forceOrientation: 'none'
    };

    var orientation = 999;

    var resizeProperties = {
        width: -1,
        height: -1,
        offsetX: 0,
        offsetY: 0,
        customClosePosition: 'top-right',
        allowOffscreen: true
    };

    var currentPosition = {
        width: -1,
        height: -1,
        x: 0,
        y: 0
    };

    var defaultPosition = {
        width: -1,
        height: -1,
        x: 0,
        y: 0
    };
 
    var maxSize = {
        width: -1,
        height: -1
    };

    var screenSize = {
        width: -1,
        height: -1
    };

    var supports = {
        'sms': false,
        'tel': false,
        'calendar': false,
        'storePicture': false,
        'inlineVideo': false
    };

    var listeners = {};

    var heading = -1;

    var tilt = {
        x: 0,
        y: 0,
        z: 0
    };
	
	var changeHandlers = {
        
        state:function(val) {
            var currentState = state;
            broadcastEvent(EVENTS.INFO, 'Setting state to ' + JSON.stringify(val, '\t'));
            broadcastEvent(EVENTS.STATECHANGE, (state=val));
            if (currentState==STATES.LOADING) {
                broadcastEvent(EVENTS.READY);
                mraidview.executeNativeCall(EVENTS.READY);
            }
        },
 
        viewable:function(val) {
            broadcastEvent(EVENTS.INFO, 'Setting viewable to ' + JSON.stringify(val, '\t'));
            broadcastEvent(EVENTS.VIEWABLECHANGE, (viewable=val));
        },
 
        expandProperties:function(val) {
            broadcastEvent(EVENTS.INFO, 'Merging expandProperties with ' + JSON.stringify(val));
            for (var i in val) {
                expandProperties[i] = val[i];
            }
        },
 
        currentPosition:function(val) {
            broadcastEvent(EVENTS.INFO, 'Merging currentPosition with ' + JSON.stringify(val));
            broadcastEvent(EVENTS.SIZECHANGE, val.width, val.height);
            for (var i in val) {
                currentPosition[i] = val[i];
            }
        },
 
        maxSize:function(val) {
            broadcastEvent(EVENTS.INFO, 'Merging maxSize with ' + JSON.stringify(val));
            for (var i in val) {
                maxSize[i] = val[i];
            }
        },
 
        defaultPosition:function(val) {
            broadcastEvent(EVENTS.INFO, 'Merging defaultPosition with ' + JSON.stringify(val));
            for (var i in val) {
                defaultPosition[i] = val[i];
            }
        },
 
        screenSize:function(val) {
            broadcastEvent(EVENTS.INFO, 'Merging screenSize with ' + JSON.stringify(val));
            for (var i in val) {
                screenSize[i] = val[i];
            }
        },
 
        supports:function(val) {
            broadcastEvent(EVENTS.INFO, 'Merging supports with ' + JSON.stringify(val));
            for (var i in val) {
                supports[i] = val[i];
            }
        },
 
        heading:function(val) {
            //broadcastEvent(EVENTS.INFO, 'Setting heading to ' + JSON.stringify(val, '\t'));
            broadcastEvent(EVENTS.HEADINGCHANGE, (heading=val));
        },
 
        tilt:function(val) {
            //broadcastEvent(EVENTS.INFO, 'Setting tilt to ' + JSON.stringify(val, '\t'));
            for (var i in val) {
                tilt[i] = val[i];
            }
            broadcastEvent(EVENTS.TILTCHANGE, tilt.x, tilt.y, tilt.z);
        },
 
        orientation:function(val) {
            broadcastEvent(EVENTS.INFO, 'Setting orientation to ' + val);
            broadcastEvent(EVENTS.ORIENTATIONCHANGE, (orientation=val));
        },
 
        location:function(val) {
            //broadcastEvent(EVENTS.INFO, 'Location change ' + JSON.stringify(val));
            broadcastEvent(EVENTS.LOCATIONCHANGE, val);
        }
    };
 
    mraidview.addEventListener('change', function(properties) {
        for (var property in properties) {
            changeHandlers[property](properties[property]);
        }
    });

    mraidview.addEventListener('error', function(message, action) {
        broadcastEvent(EVENTS.ERROR, message, action);
    });


    var EventListeners = function(event) {
        
        var listeners = {};
        this.event = event;
        this.count = 0;
 
        this.add = function(func) {
            var id = String(func);
            if (!listeners[id]) {
                listeners[id] = func;
                this.count++;
                if (this.count==1) {
                    mraidview.executeNativeCall({activateSensor:event});
                }
            }
        };
 
        this.remove = function(func) {
            var id = String(func);
            if (listeners[id]) {
                listeners[id] = null;
                delete listeners[id];
                this.count--;
                if (this.count==0) {
                    mraidview.executeNativeCall({deactivateSensor:event});
                }
                return true;
            }
            return false;
        };
 
        this.removeAll = function() {
            for (var id in listeners) {
                this.remove(listeners[id]);
            }
        };
 
        this.broadcast = function(args) {
            for (var id in listeners) {
                listeners[id].apply({}, args);
            }
        };
 
        this.toString = function() {
            var out = [event,':'];
            for (var id in listeners) {
                out.push('|', id, '|');
            }
            return out.join('');
        };
	};
 
    var broadcastEvent = function() {
        var args = new Array(arguments.length);
        for (var i = 0; i<arguments.length; i++) {
            args[i] = arguments[i];
        }
        var event = args.shift();
        try {
            if (listeners[event]) {
                listeners[event].broadcast(args);
            }
        } catch (e) {}
    };
 
    var contains = function(value, array) {
        for (var i in array) {
            if (array[i]==value) {
                return true;
            }
        }
        return false;
    };
	
    var valid = function(obj, validators, action, full) {
        if (full) {
            if (obj===undefined) {
                broadcastEvent(EVENTS.ERROR, 'Required object missing.', action);
                return false;
            } else {
                for (var i in validators) {
                    if (obj[i]===undefined) {
                        broadcastEvent(EVENTS.ERROR, 'Object missing required property '+i,action);
                        return false;
                    }
                }
            }
        }
        for (var i in obj) {
            if (!validators[i]) {
                broadcastEvent(EVENTS.ERROR, 'Invalid property specified - '+i+'.', action);
                return false;
            } else if (!validators[i](obj[i])) {
                broadcastEvent(EVENTS.ERROR, 'Value of property '+i+'<'+obj[i]+'>'+' is not valid type.',action);
                return false;
            }
        }
        return true;
    };
	
    var expandPropertyValidators = {
        width:function(value) {
            return !isNaN(value) && value >= 0
        },
        height:function(value) {
            return !isNaN(value) && value >= 0
        },
        useCustomClose:function(value) {
            return (value===true || value===false);
        },
        isModal:function(value) {
            return (value===true);
        }
    };
	
    var orientationPropertyValidators = {
        allowOrientationChange:function(value) {
            return (value===true || value===false);
        },
        forceOrientation:function(value) {
            return (value=='portrait' || value=='landscape' || value=='none');
        }
    };
	
    var resizePropertyValidators = {
        width:function(value) {
            return !isNaN(value) && value>=0
        },
        height:function(value) {
            return !isNaN(value) && value>=0
        },
        offsetX:function(value) {
            return !isNaN(value)
        },
        offsetY:function(value) {
            return !isNaN(value)
        },
        customClosePosition:function(value) {
            return (value=='top-left' || value=='top-right' || value=='center' || value=='bottom-left' || value=='bottom-right' || value=='top-center' || value=='bottom-center');
        },
        allowOffscreen:function(value) {
            return (value===true || value===false);
        },
    };
	
    var calendarPropertyValidators = {
        
        id:function(value) {
            return typeof value=='string' || (typeof value=='object' && value.constructor===String);
        },
        
        description:function(value) {
            return typeof value=='string' || (typeof value=='object' && value.constructor===String);
        },
        
        location:function(value) {
            return typeof value=='string' || (typeof value=='object' && value.constructor===String);
        },
        
        summary:function(value) {
            return typeof value=='string' || (typeof value=='object' && value.constructor===String);
        },
        
        start:function(value) {
            if (Date.parse(value) || value!=null) {
                return true;
            }
            return false;
            //if (value.match(/\d{4}\-\d\d\-\d\d[tT]\d\d:\d\d[+\-]\d\d:\d\d/)) {return true;}
            //return false;
        },
        
        end:function(value) {
            if (Date.parse(value) || value!=null) {
                return true;
            }
            return false;
        },
        
        status:function(value) {
            return (value=='pending' || value=='tentative' || value=='confirmed' || value=='cancelled');
        },
        
        transparency:function(value) {
            return (value=='transparent' || value=='opaque');
        },
        
        reminder:function(value) {
            if (value!=null && isNaN(value) && !Date.parse(value)){
                return false;
            }
            return true;
        },
        
        recurrence:function(value) {
            if (value.frequency!=null && (value.frequency!='daily' && value.frequency!='weekly' && value.frequency!='monthly' && value.frequency!='yearly')) return false;
            if (value.interval!=null && isNaN(value.interval)) return false;
            if (value.expires!=null && !Date.parse(value.expires)) return false;
            if (value.exceptionDates!=null && !(value.exceptionDates instanceof Array)) return false;
            if (value.daysInWeek!=null && !(value.daysInWeek instanceof Array)) return false;
            if (value.daysInMonth!=null && !(value.daysInMonth instanceof Array)) return false;
            if (value.daysInYear!=null && !(value.daysInYear instanceof Array)) return false;
            if (value.weeksInMonth!=null && !(value.weeksInMonth instanceof Array)) return false;
            if (value.monthsInYear!=null && !(value.monthsInYear instanceof Array)) return false;
            return true;
        }
	};
	
    mraid.addDefaultCloseButton = function() {
        if (expandProperties.useCustomClose) {
            return;
        }
        mraid.removeCloseButton();
        var div = document.createElement('div');
        div.id = 'mraid_close';
        div.innerHTML = '<a style="position:fixed;top:0px;right:0px;width:30px;height:30px;margin:10px;background-color:#262626;display:block;background-size:10px 10px;border-radius:15px;background-repeat:no-repeat;background-position:50% 50%;background-image:url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABQAAAAUCAYAAACNiR0NAAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAAFiQAABYkBbWid+gAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAAAEvSURBVDiNpdQxTsMwFAbg/7104gLcBQkpnhhg6MBAToHEVHGAjpU4RRdGGDokjsraE3CDXqBT8x6Lg4xqvzjiSVEi2/ry7PwKtW17w8xvRHQSkbVzbocZ5b2/Z+aNqh5FZEXe+z2A2zB/BtDUdf1egvV9/whgC2ARhg5MRNfRmgWAbVg4FwMRnVhEXkJnxWgKA3AWkTU75z4BNKVoDgPQOOd2DADhzCZRCxvPnVS16O3h2cQuQAMdwr2ysCRooHFl48Wp1dGZDonpIYdlwf9UEoy2XCWmKxg5vQCNjxJvP5vTP6ARm6dwTYb/F5wKbWn4uQQbB0pQ6rrujog+prC4cg2o6pKZ+XUOZnXKzBtW1as5mIWq6pFF5BnAFxF9q+qy9G89oqr6QER7AAcRWf0AiArUTFrBeYkAAAAASUVORK5CYII=);" href="#" onclick="mraid.close();return false;"></a>';
        document.body.appendChild(div);
        div.style.position='fixed';
        div.style.zIndex='2147483647';
        div.style.padding='0px';
        div.style.top='0px';
        div.style.right='0px';
    }
 
    mraid.removeCloseButton = function() {
        var el = document.getElementById('mraid_close');
        if (el!=null) {
            el.parentNode.removeChild(el);
        }
    }
	
    mraid.addCustomClosePosition = function() {
        mraid.removeCloseButton();
        var div = document.createElement('div');
        div.id = 'mraid_close';
        div.innerHTML = '<a style="position:fixed;width:50px;height:50px;margin:0px;background-color:rgba(0,0,0,0);display:block;" href="#" onclick="mraid.close();return false;"></a>';
        document.body.appendChild(div);
        div.style.position = 'fixed';
        div.style.zIndex = '2147483647';
        div.style.padding = '0px';
        div.style.width = '50px';
        div.style.height = '50px';
        
        switch (resizeProperties.customClosePosition) {
            case 'top-left':
                div.style.top='0px';
                div.style.left='0px';
                break;
            case 'top-right':
                div.style.top='0px';
                div.style.right='0px';
                break;
            case 'center':
                div.style.top='50%';
                div.style.marginTop='-25px';
                div.style.left='50%';
                div.style.marginLeft='-25px';
                break;
            case 'bottom-left':
                div.style.bottom='0px';
                div.style.left='0px';
                break;
            case 'bottom-right':
                div.style.bottom='0px';
                div.style.right='0px';
                break;
            case 'top-center':
                div.style.top='0px';
                div.style.left='50%';
                div.style.marginLeft='-25px';
                break;
            case 'bottom-center':
                div.style.bottom='0px';
                div.style.left='50%';
                div.style.marginLeft='-25px';
                break;
            default:
                div.style.top='0px';
                div.style.right='0px';
        }
    }
	
    mraid.getVersion = function() {
        return version;
    };

    mraid.getState = function() {
        return state;
    };

    mraid.getPlacementType = function() {
        return placementType;
    };

    mraid.isViewable = function() {
        return viewable;
    };

    mraid.getExpandProperties = function() {
        return expandProperties;
    };

    mraid.setExpandProperties = function(properties) {
        if (valid(properties, expandPropertyValidators, 'setExpandProperties', false)) {
            for (var i in properties) {
                expandProperties[i]=properties[i];
            }
        }
    };

    mraid.getOrientationProperties = function() {
        return orientationProperties;
    };

    // Must set the whole JavaScript object
    mraid.setOrientationProperties = function(properties) {
        if (valid(properties, orientationPropertyValidators, 'setOrientationProperties', false)) {
            for (var i in properties) {
                orientationProperties[i]=properties[i];
            }
            mraidview.executeNativeCall({setOrientationProperties:orientationProperties});
        }
    };

    mraid.getOrientation = function() {
        return orientation
    };

    mraid.getResizeProperties = function() {
        return resizeProperties;
    };

    mraid.setResizeProperties = function(properties) {
        if (valid(properties, resizePropertyValidators, 'setResizeProperties', false)) {
            for (var i in properties) {
                resizeProperties[i]=properties[i];
            }
        }
    };

    mraid.getCurrentPosition = function() {
        return currentPosition;
    };

    mraid.getMaxSize = function() {
        return maxSize;
    };

    mraid.getDefaultPosition = function() {
        return defaultPosition;
    };

    mraid.getScreenSize = function() {
        return screenSize;
    };

    mraid.supports = function(feature) {
        return supports[feature];
    };
 
    mraid.addEventListener = function(event, listener) {
        if (!event || !listener) {
            broadcastEvent(EVENTS.ERROR, 'Both event and listener are required.', 'addEventListener');
        } else if (!contains(event, EVENTS)) {
            broadcastEvent(EVENTS.ERROR, 'Unknown event: '+event, 'addEventListener');
        }
        else if (!listeners[event]) {
            listeners[event] = new EventListeners(event);listeners[event].add(listener);
        }
    };
	
    mraid.removeEventListener = function(event, listener) {
        if (!event) {
            broadcastEvent(EVENTS.ERROR, 'Must specify an event.', 'removeEventListener');
        } else {
            if (listener && (!listeners[event] || !listeners[event].remove(listener))) {
                broadcastEvent(EVENTS.ERROR, 'Listener not currently registered for event', 'removeEventListener');
                return;
            } else if (listeners[event]) {
                listeners[event].removeAll();
            }
            if (listeners[event] && listeners[event].count==0) {
                listeners[event] = null;
                delete listeners[event];
            }
        }
    };
	
    mraid.open = function(URL) {
        if (!URL) {
            broadcastEvent(EVENTS.ERROR, 'URL is required.', 'open');
            return;
        }
        mraidview.executeNativeCall({open:URL});
    }
	
    mraid.expand = function(URL) {
        if (state != STATES.DEFAULT && state!=STATES.RESIZED) {
            broadcastEvent(EVENTS.ERROR, 'Cannot expand an ad that is not in the default or resized state.', 'expand');
            return;
        }
        if (URL!=null) {
            mraid.open(URL);
            return;
        }
        mraidview.executeNativeCall({expand:{expandProperties:expandProperties,orientationProperties:orientationProperties}});
    }
	
    mraid.resize = function() {
        if (state != STATES.DEFAULT && state!=STATES.RESIZED) {
            broadcastEvent(EVENTS.ERROR, 'Cannot resize an ad that is not in the default or resized state.', 'resize');
            return;
        }
        if (!valid(resizeProperties, resizePropertyValidators, 'resize', true)) {
            broadcastEvent(EVENTS.ERROR, 'Set resize properties', 'resize');
            return;
        }
        mraidview.executeNativeCall({resize:resizeProperties});
    }

    mraid.close = function() {
        mraidview.executeNativeCall('close');
    };

    mraid.storePicture = function(URI) {
        mraidview.executeNativeCall({storePicture:URI});
    }

    mraid.createCalendarEvent = function(parameters) {
        if (!valid(parameters, calendarPropertyValidators, 'createCalendarEvent', false)) {
            return;
        }
        mraidview.executeNativeCall({createCalendarEvent:parameters});
    }

    mraid.playVideo = function(URI) {
        mraidview.executeNativeCall({playVideo:URI});
    }

    mraid.adgear.getHeading = function() {
        return heading;
    };

    mraid.adgear.getTilt = function() {
        return tilt;
    };

    mraid.adgear.setDisallowParentInterceptTouchEvent = function(val) {
        mraidview.executeNativeCall({setDisallowParentInterceptTouchEvent:val});
    }

})();