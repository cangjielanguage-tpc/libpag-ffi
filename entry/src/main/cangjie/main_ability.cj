package ohos_app_cangjie_entry

import kit.PerformanceAnalysisKit.Hilog
internal import ohos.ability.AbilityStage
internal import ohos.ability.LaunchReason
import ohos.ability.*
import ohos.window.WindowStage

var globalAbilityContext: Option<AbilityContext> = Option<AbilityContext>.None

class MainAbility <: UIAbility {
    public init() {
        super()
        registerSelf()
    }

    public override func onCreate(want: Want, launchParam: LaunchParam): Unit {
        globalAbilityContext = Option<AbilityContext>.Some(this.context)
        Hilog.info(1, "Cangjie", "MainAbility OnCreated.${want.abilityName}")
        match (launchParam.launchReason) {
            case LaunchReason.START_ABILITY => Hilog.info(1, "Cangjie", "START_ABILITY")
            case _ => ()
        }
    }

    public override func onWindowStageCreate(windowStage: WindowStage): Unit {
        Hilog.info(1, "Cangjie", "MainAbility onWindowStageCreate.")
        windowStage.loadContent("EntryView")
    }
}
