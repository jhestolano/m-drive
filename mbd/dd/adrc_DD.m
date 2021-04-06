Ts = 1.0e-4;

h = Ts;
r = 10.0;
h0 = h;
r0 = r;

%% ADRC Control parameters.
ADRC_TrackFil_h0 = Simulink.Parameter;
ADRC_TrackFil_h0.StorageClass = 'Auto';
ADRC_TrackFil_h0.Description = 'h0: Usually matches execution rate of filter.';
ADRC_TrackFil_h0.DataType = 'single';
ADRC_TrackFil_h0.Min = [];
ADRC_TrackFil_h0.Max = [];
ADRC_TrackFil_h0.DocUnits = '';
ADRC_TrackFil_h0.Value = 1e-3;

ADRC_TrackFil_ts = Simulink.Parameter;
ADRC_TrackFil_ts.StorageClass = 'Auto';
ADRC_TrackFil_ts.Description = 'Tracking filter exeuction rate.';
ADRC_TrackFil_ts.DataType = 'single';
ADRC_TrackFil_ts.Min = [];
ADRC_TrackFil_ts.Max = [];
ADRC_TrackFil_ts.DocUnits = '';
ADRC_TrackFil_ts.Value = 1e-3;

ADRC_TrackFil_r0 = Simulink.Parameter;
ADRC_TrackFil_r0.StorageClass = 'Auto';
ADRC_TrackFil_r0.Description = 'Tracking filter agressivenes.';
ADRC_TrackFil_r0.DataType = 'single';
ADRC_TrackFil_r0.Min = [];
ADRC_TrackFil_r0.Max = [];
ADRC_TrackFil_r0.DocUnits = '';
ADRC_TrackFil_r0.Value = 1.e3;

%% Disturbance observer gains.
ADRC_DistObsK1 = Simulink.Parameter;
ADRC_DistObsK1.StorageClass = 'Auto';
ADRC_DistObsK1.Description = 'Disturbance observer gain 1.';
ADRC_DistObsK1.DataType = 'single';
ADRC_DistObsK1.Value = AdrcParams.K1;

ADRC_DistObsK2 = Simulink.Parameter;
ADRC_DistObsK2.StorageClass = 'Auto';
ADRC_DistObsK2.Description = 'Disturbance observer gain 2.';
ADRC_DistObsK2.DataType = 'single';
ADRC_DistObsK2.Value = AdrcParams.K2;

ADRC_DistObsK3 = Simulink.Parameter;
ADRC_DistObsK3.StorageClass = 'Auto';
ADRC_DistObsK3.Description = 'Disturbance observer gain 3.';
ADRC_DistObsK3.DataType = 'single';
ADRC_DistObsK3.Value = AdrcParams.K3;
