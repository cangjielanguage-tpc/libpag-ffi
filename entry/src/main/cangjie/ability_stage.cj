package ohos_app_cangjie_entry

import ohos.ability.AbilityStage
import kit.PerformanceAnalysisKit.Hilog

class MyAbilityStage <: AbilityStage {
    public override func onCreate(): Unit {
        Hilog.info(1, "Cangjie", "MyAbilityStage onCreated.")
    }
}
