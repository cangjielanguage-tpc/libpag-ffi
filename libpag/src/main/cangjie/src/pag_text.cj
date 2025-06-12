/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

public enum PAGTextJustification {
  | Left   //0
  | Center //1
  | Right  //2
  | FullJustifyLastLineLeft   //3
  | FullJustifyLastLineRight  //4
  | FullJustifyLastLineCenter //5
  | FullJustifyLastLineFull   //6

    public func justificationToUint8(value: PAGTextJustification): UInt8 {
        match (value) {
            case PAGTextJustification.Left => 0
            case PAGTextJustification.Center => 1
            case PAGTextJustification.Right => 2
            case PAGTextJustification.FullJustifyLastLineLeft => 3
            case PAGTextJustification.FullJustifyLastLineRight => 4
            case PAGTextJustification.FullJustifyLastLineCenter => 5
            case PAGTextJustification.FullJustifyLastLineFull => 6
            case _ => 0
        }
    }
}

public class PAGText <: ToString {
    /**
     * When true, the text layer shows a fill.
     */
    public var applyFill: Bool = true
    /**
     * When true, the text layer shows a stroke.
     */
    public var applyStroke: Bool = false
    /**
     * Readonly, external modifications are not valid.
     */
    public var baselineShift: Float32 = 0.0
    /**
     * When true, the text layer is paragraph (bounded) text.
     * Readonly, external modifications are not valid.
     */
    public var boxText: Bool = false
    /**
     * For box text, the pixel boundary for the text bounds.
     * Readonly, external modifications are not valid.
     */
    public var boxTextRect: Rect = Rect(
      left: 0.0,
      top: 0.0,
      right: 0.0,
      bottom: 0.0
    )
    /**
     * Readonly, external modifications are not valid.
     */
    public var firstBaseLine: Float32 = 0.0
    public var fauxBold: Bool = false
    public var fauxItalic: Bool = false
    /**
     * The text layer’s fill color.
     */
    public var fillColor: UInt32 = 0
    /**
     * A string with the name of the font family.
     **/
    public var fontFamily: String = ""
    /**
     * A string with the style information — e.g., “bold”, “italic”.
     **/
    public var fontStyle: String = ""
    /**
     * The text layer’s font size in pixels.
     */
    public var fontSize: Float32 = 24.0
    /**
     * The text layer’s stroke color.
     */
    public var strokeColor: UInt32 = 0
    /**
     * Indicates the rendering order for the fill and stroke of a text layer.
     * Readonly, external modifications are not valid.
     */
    public var strokeOverFill: Bool = true
    /**
     * The text layer’s stroke thickness.
     */
    public var strokeWidth: Float32 = 1.0
    /**
     * The text layer’s Source Text value.
     */
    public var text: String = ""
    /**
     * The paragraph justification for the text layer. Such as : PAGJustificationLeftJustify, PAGJustificationCenterJustify...
     */
    public var justification: PAGTextJustification = PAGTextJustification.Left
    /**
     * The space between lines, 0 indicates 'auto', which is fontSize * 1.2
     */
    public var leading: Float32 = 0.0
    /**
     * The text layer’s spacing between characters.
     */
    public var tracking: Float32 = 0.0
    /**
     * The text layer’s background color.
     */
    public var backgroundColor: UInt32 = 0
    /**
     * The text layer’s background alpha. 0 = 100% transparent, 255 = 100% opaque.
     */
    public var backgroundAlpha: UInt8 = 255

    public func toString(): String {
        let str: String = '''
                                            PAGText:
                                            (applyFill = ${applyFill}),
                                            (applyStroke = ${applyStroke}),
                                            (baselineShift = ${baselineShift}),
                                            (boxText = ${boxText}),
                                            (boxTextRect= ${boxTextRect.toString()}),
                                            (firstBaseLine = ${firstBaseLine}),
                                            (fauxBold = ${fauxBold}),
                                            (fauxItalic = ${fauxItalic}),
                                            (fillColor = ${fillColor}),
                                            (fontSize = ${fontSize}),
                                            (strokeColor = ${strokeColor}),
                                            (strokeOverFill = ${strokeOverFill}),
                                            (strokeWidth = ${strokeWidth}),
                                            (justification = ${justification.justificationToUint8(justification)}),
                                            (leading = ${leading}),
                                            (tracking = ${tracking}),
                                            (backgroundColor = ${backgroundColor}),
                                            (backgroundAlpha = ${backgroundAlpha}),
                                            (fontFamily = ${fontFamily}),
                                            (fontStyle = ${fontStyle}),
                                            (text = ${text})
                                            '''
        return str
    }
}
