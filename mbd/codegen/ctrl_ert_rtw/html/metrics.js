function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDW"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl.c",
	size: 185};
	 this.metricsArray.var["rtP"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_data.c",
	size: 610};
	 this.metricsArray.var["rtU"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl.c",
	size: 20};
	 this.metricsArray.var["rtY"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl.c",
	size: 68};
	 this.metricsArray.fcn["Ctrl_Fast"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl.c",
	stack: 0,
	stackTotal: 29};
	 this.metricsArray.fcn["Ctrl_Init"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["Ctrl_Slow"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl.c",
	stack: 0,
	stackTotal: 35};
	 this.metricsArray.fcn["ctrl_fast"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_fast.c",
	stack: 29,
	stackTotal: 29};
	 this.metricsArray.fcn["ctrl_fast.c:autocal_in_progress"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_fast.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["ctrl_fast_Init"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_fast.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["ctrl_slow"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_slow.c",
	stack: 35,
	stackTotal: 35};
	 this.metricsArray.fcn["ctrl_slow_Init"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_slow.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fabsf"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_fast.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fmaxf"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_fast.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["sqrtf"] = {file: "/home/elrobotista/Repos/bldc/mbd/codegen/ctrl_ert_rtw/ctrl_fast.c",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="ctrl_metrics.html">Global Memory: 883(bytes) Maximum Stack: 35(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
