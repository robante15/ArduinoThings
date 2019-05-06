!function(r,a){"use strict";var o,u,c=r.document,l=[],i=[],d={},s={},e="async"in c.createElement("script")||"MozAppearance"in c.documentElement.style||r.opera,t=r.head_conf&&r.head_conf.head||"head",f=r[t]=r[t]||function(){f.ready.apply(null,arguments)},n=1,p=2,y=3,h=4;function m(){}function v(e,t){if(e){"object"==typeof e&&(e=[].slice.call(e));for(var n=0,a=e.length;n<a;n++)t.call(e,e[n],n)}}function g(e,t){var n=Object.prototype.toString.call(t).slice(8,-1);return t!==a&&null!==t&&n===e}function L(e){return g("Function",e)}function E(e){return g("Array",e)}function T(e){(e=e||m)._done||(e(),e._done=1)}function b(e){var t,n,a,r,o={};if("object"==typeof e)for(var u in e)e[u]&&(o={name:u,url:e[u]});else o={name:(t=e,n=t.split("/"),a=n[n.length-1],r=a.indexOf("?"),-1!==r?a.substring(0,r):a),url:e};var c=s[o.name];return c&&c.url===o.url?c:s[o.name]=o}function j(e){for(var t in e=e||s)if(e.hasOwnProperty(t)&&e[t].state!==h)return!1;return!0}function A(t,e){t.state===a&&(t.state=n,t.onpreload=[],w({url:t.url,type:"cache"},function(){var e;(e=t).state=p,v(e.onpreload,function(e){e.call()})}))}function S(e,t){t=t||m,e.state!==h?e.state!==y?e.state!==n?(e.state=y,w(e,function(){e.state=h,t(),v(d[e.name],function(e){T(e)}),u&&j()&&v(d.ALL,function(e){T(e)})})):e.onpreload.push(function(){S(e,t)}):f.ready(e.name,t):t()}function w(e,t){var n;t=t||m,/\.css[^\.]*$/.test(e.url)?((n=c.createElement("link")).type="text/"+(e.type||"css"),n.rel="stylesheet",n.href=e.url):((n=c.createElement("script")).type="text/"+(e.type||"javascript"),n.src=e.url),n.onload=n.onreadystatechange=function(e){("load"===(e=e||r.event).type||/loaded|complete/.test(n.readyState)&&(!c.documentMode||c.documentMode<9))&&(n.onload=n.onreadystatechange=n.onerror=null,t())},n.onerror=function(e){e=e||r.event,n.onload=n.onreadystatechange=n.onerror=null,t()},n.async=!1,n.defer=!1;var a=c.head||c.getElementsByTagName("head")[0];a.insertBefore(n,a.lastChild)}function M(){if(!c.body)return r.clearTimeout(f.readyTimeout),void(f.readyTimeout=r.setTimeout(M,50));u||(u=!0,function(){for(var e=c.getElementsByTagName("script"),t=0,n=e.length;t<n;t++){var a=e[t].getAttribute("data-headjs-load");if(a)return f.load(a)}}(),v(l,function(e){T(e)}))}function O(){c.addEventListener?(c.removeEventListener("DOMContentLoaded",O,!1),M()):"complete"===c.readyState&&(c.detachEvent("onreadystatechange",O),M())}if("complete"===c.readyState)M();else if(c.addEventListener)c.addEventListener("DOMContentLoaded",O,!1),r.addEventListener("load",M,!1);else{c.attachEvent("onreadystatechange",O),r.attachEvent("onload",M);var k=!1;try{k=!r.frameElement&&c.documentElement}catch(e){}k&&k.doScroll&&function t(){if(!u){try{k.doScroll("left")}catch(e){return r.clearTimeout(f.readyTimeout),void(f.readyTimeout=r.setTimeout(t,50))}M()}}()}f.load=f.js=e?function(){var e=arguments,n=e[e.length-1],a={};return L(n)||(n=null),E(e[0])?(e[0].push(n),f.load.apply(null,e[0])):(v(e,function(e,t){e!==n&&(e=b(e),a[e.name]=e)}),v(e,function(e,t){e!==n&&S(e=b(e),function(){j(a)&&T(n)})})),f}:function(){var e=arguments,t=[].slice.call(e,1),n=t[0];return o?n?(v(t,function(e){!L(e)&&e&&A(b(e))}),S(b(e[0]),L(n)?n:function(){f.load.apply(null,t)})):S(b(e[0])):i.push(function(){f.load.apply(null,e)}),f},f.test=function(e,t,n,a){var r="object"==typeof e?e:{test:e,success:!!t&&(E(t)?t:[t]),failure:!!n&&(E(n)?n:[n]),callback:a||m},o=!!r.test;return o&&r.success?(r.success.push(r.callback),f.load.apply(null,r.success)):!o&&r.failure?(r.failure.push(r.callback),f.load.apply(null,r.failure)):a(),f},f.ready=function(e,t){if(e===c)return u?T(t):l.push(t),f;if(L(e)&&(t=e,e="ALL"),E(e)){var n={};return v(e,function(e){n[e]=s[e],f.ready(e,function(){j(n)&&T(t)})}),f}if("string"!=typeof e||!L(t))return f;var a=s[e];if(a&&a.state===h||"ALL"===e&&j()&&u)return T(t),f;var r=d[e];return r?r.push(t):r=d[e]=[t],f},f.ready(c,function(){o&&j()&&v(d.ALL,function(e){T(e)}),f.feature&&f.feature("domloaded",!0)}),setTimeout(function(){o=!0,v(i,function(e){e()})},300)}(window),function(e,t){e.headJsLoaded=function(e){e(t)};var n=e.headJsLoadedQueue||[],a=n.length;if(n.length)for(var r=n.splice(0),o=0;o<a;o++)r[o][0](t)}(window,head);