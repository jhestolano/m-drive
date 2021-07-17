classdef CalMgrSt_T < Simulink.IntEnumType
    % CalMgrSt_T Calibration manager State.
    %   Defines the manager control mode status/state.
    enumeration
      ST_FAILED(-1),
      ST_NOT_STARTED(0),
      ST_ENC_OFS(1),
      ST_RES_ID(2),
      ST_IND_ID(3),
      ST_IFBK_OFS_CAL(4),
      ST_DONE(255),
    end

    methods (Static)
      function retVal = getDataScope()
        retVal = 'Exported';
      end
    end
end

