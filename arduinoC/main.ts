/**
 * QRCode Scanner blocks
 */
//% weight=100 color=#0fbc11 icon="\uf00a"
namespace QRCodeScanner {
    //% block="Initialize QR Code Scanner" blockType="command"
    export function initScanner(): void {
        Generator.addInclude("DFRobot_GM60", "#include <DFRobot_GM60.h>");
        Generator.addObject("gm60", "DFRobot_GM60_IIC", "gm60;");
        Generator.addSetup("gm60_begin", "gm60.begin();");
        Generator.addSetup("gm60_reset", "gm60.reset();");
        Generator.addSetup("gm60_encode", "gm60.encode(gm60.eUTF8);");
        Generator.addSetup("gm60_setupCode", "gm60.setupCode(/*on=*/true,/*content=*/true);");
        Generator.addSetup("gm60_setIdentify", "gm60.setIdentify(gm60.eEnableAllBarcode);");
    }

    //% block="Read QR Code data" blockType="reporter"
    export function readQRCode(): string {
        return Generator.addCode(["gm60.detection()", Generator.ORDER_UNARY_POSTFIX]);
    }
}
