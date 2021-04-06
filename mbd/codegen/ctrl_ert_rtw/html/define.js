function CodeDefine() { 
this.def = new Array();
this.def["ctrl_rtZDBG_BUS"] = {file: "ctrl_c.html",line:14,type:"var"};
this.def["rtDW"] = {file: "ctrl_c.html",line:29,type:"var"};
this.def["rtU"] = {file: "ctrl_c.html",line:32,type:"var"};
this.def["rtY"] = {file: "ctrl_c.html",line:35,type:"var"};
this.def["Ctrl_Slow"] = {file: "ctrl_c.html",line:38,type:"fcn"};
this.def["Ctrl_Fast"] = {file: "ctrl_c.html",line:63,type:"fcn"};
this.def["Ctrl_Init"] = {file: "ctrl_c.html",line:86,type:"fcn"};
this.def["DW"] = {file: "ctrl_h.html",line:34,type:"type"};
this.def["ExtU"] = {file: "ctrl_h.html",line:43,type:"type"};
this.def["ExtY"] = {file: "ctrl_h.html",line:54,type:"type"};
this.def["MtrCtrlMd"] = {file: "ctrl_types_h.html",line:25,type:"type"};
this.def["struct_CI8nDHNKFYq3miU7okN8NH"] = {file: "ctrl_types_h.html",line:43,type:"type"};
this.def["P_ctrl_fast"] = {file: "ctrl_types_h.html",line:48,type:"type"};
this.def["P_ctrl_slow"] = {file: "ctrl_types_h.html",line:51,type:"type"};
this.def["P"] = {file: "ctrl_types_h.html",line:54,type:"type"};
this.def["autocal_in_progress"] = {file: "ctrl_fast_c.html",line:46,type:"fcn"};
this.def["ctrl_fast_Init"] = {file: "ctrl_fast_c.html",line:220,type:"fcn"};
this.def["ctrl_fast"] = {file: "ctrl_fast_c.html",line:293,type:"fcn"};
this.def["DW_ctrl_fast"] = {file: "ctrl_fast_h.html",line:58,type:"type"};
this.def["ctrl_slow_Init"] = {file: "ctrl_slow_c.html",line:19,type:"fcn"};
this.def["ctrl_slow"] = {file: "ctrl_slow_c.html",line:73,type:"fcn"};
this.def["DW_ctrl_slow"] = {file: "ctrl_slow_h.html",line:32,type:"type"};
this.def["rtP"] = {file: "ctrl_data_c.html",line:15,type:"var"};
this.def["AutoCalSt"] = {file: "AutoCalSt_h.html",line:18,type:"type"};
this.def["DBG_BUS"] = {file: "DBG_BUS_h.html",line:18,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:42,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:43,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:44,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:45,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:46,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:59,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:81,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "/";
var isPC = false;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ctrl_c.html"] = "../ctrl.c";
	this.html2Root["ctrl_c.html"] = "ctrl_c.html";
	this.html2SrcPath["ctrl_h.html"] = "../ctrl.h";
	this.html2Root["ctrl_h.html"] = "ctrl_h.html";
	this.html2SrcPath["ctrl_private_h.html"] = "../ctrl_private.h";
	this.html2Root["ctrl_private_h.html"] = "ctrl_private_h.html";
	this.html2SrcPath["ctrl_types_h.html"] = "../ctrl_types.h";
	this.html2Root["ctrl_types_h.html"] = "ctrl_types_h.html";
	this.html2SrcPath["ctrl_fast_c.html"] = "../ctrl_fast.c";
	this.html2Root["ctrl_fast_c.html"] = "ctrl_fast_c.html";
	this.html2SrcPath["ctrl_fast_h.html"] = "../ctrl_fast.h";
	this.html2Root["ctrl_fast_h.html"] = "ctrl_fast_h.html";
	this.html2SrcPath["ctrl_slow_c.html"] = "../ctrl_slow.c";
	this.html2Root["ctrl_slow_c.html"] = "ctrl_slow_c.html";
	this.html2SrcPath["ctrl_slow_h.html"] = "../ctrl_slow.h";
	this.html2Root["ctrl_slow_h.html"] = "ctrl_slow_h.html";
	this.html2SrcPath["ctrl_data_c.html"] = "../ctrl_data.c";
	this.html2Root["ctrl_data_c.html"] = "ctrl_data_c.html";
	this.html2SrcPath["AutoCalSt_h.html"] = "../AutoCalSt.h";
	this.html2Root["AutoCalSt_h.html"] = "AutoCalSt_h.html";
	this.html2SrcPath["DBG_BUS_h.html"] = "../DBG_BUS.h";
	this.html2Root["DBG_BUS_h.html"] = "DBG_BUS_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ctrl_c.html","ctrl_h.html","ctrl_private_h.html","ctrl_types_h.html","ctrl_fast_c.html","ctrl_fast_h.html","ctrl_slow_c.html","ctrl_slow_h.html","ctrl_data_c.html","AutoCalSt_h.html","DBG_BUS_h.html","rtwtypes_h.html","rtmodel_h.html"];
