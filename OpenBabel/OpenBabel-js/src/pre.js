// Set essetial enviroment vars for OpenBabel
if (typeof(Module) === 'undefined')
{
  Module = {};
  Module.preRun = [function() {ENV.BABEL_DATADIR = "data"}];
}
else
{
  Module.preRun.push(function() {ENV.BABEL_DATADIR = "data"})  
}
Module.logReadFiles = true;