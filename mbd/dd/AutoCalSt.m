classdef AutoCalSt < Simulink.IntEnumType
    % AUTOCALST Auto-Calibration State.
    %   Defines the auto-calibration status/state.
    enumeration
      ErrIndTooSmall(-1),
      ErrIndTooLarge(-2),
      ErrResTooSmall(-3),
      ErrResTooLarge(-4),
      NotStarted(0),
      IndID(1);
      IndIDCoolDown(2),
      ResID(3)
      IfbkOfsID(4)
      TrqCnstID(5)
      InertiaID(6)
      Done(255),
    end

    methods (Static)
      function retVal = getDataScope()
        retVal = 'Exported';
      end
    end
end

