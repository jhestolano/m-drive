classdef CtrlMgrSt < Simulink.IntEnumType
    % CTRLMGRST Control mode manager State.
    %   Defines the manager control mode status/state.
    enumeration
      ErrIndTooSmall(-1),
      ErrIndTooLarge(-2),
      ErrResTooSmall(-3),
      ErrResTooLarge(-4),
      NotStarted(0),
      AnglOfsCal(1),
      IndID(2);
      IndIDCoolDown(3),
      ResID(4)
      IfbkOfsID(5)
      TrqCnstID(6)
      InertiaID(7)
      Done(255),
    end

    methods (Static)
      function retVal = getDataScope()
        retVal = 'Exported';
      end
    end
end

