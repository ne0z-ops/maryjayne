#pragma once
namespace Offsets // this is offsets.
{
    int BaseNetworkable = 0xbe7fb88; // this can be a Dec or Hex
    int GChandel = 0xC057BA0; // this can be a Dec or Hex
    int CameraOff = 0xbedd6a8; // this can be a Dec or Hex

    int Model = 0xC8;
    int boneTransforms = 0x50;
    int _displayName = 0x3F8;
    int playerFlags = 0x558;
    int lifestate = 0x234;
    int PlayerModel = 0x5B0; // and or model state
    int PlayerPos = 0x1D8;
    int PlayerInput = 0x568;
    int UserIDString = 0x2F0;
    int newRecoilOverride = 0x80;
    int recoil = 0x340;
    int recoilYawMin = 0x18;
    int recoilYawMax = 0x1C;
    int recoilPitchMin = 0x20;
    int recoilPitchMax = 0x24;
    int containerBelt = 0x30; // im pretty sure this is wher eu would put the mf clothing belt
    int ClosingBelt = 0x28; // Assuming this was a typo and should match the new 'belt' offset
    int Playerinventory = 0x3E0;
    int clActiveItem = 0x460;
    int ItemDefinition = 0x60;
    int Itemuid = 0xC8;
    int ItemAmmount = 0xB0; // Updated based on 'amount' in the new item namespace
    int heldEntity = 0x18;
    int itemlist = 0x38;
    int BPlayerEyes = 0x478;
    int bodyAngles = 0x44;
    int bodyRotation = 0x50;
    int CameraViewMatrix = 0x30C;
    int selectedViewMode = 0x35C;
    int clientTeam = 0x430;
    int TOD_Sky = 0xBCA0618; // Updated to the new pointer
    int NightParameters = 0x60;
    int DayParameters = 0x58;
    int TOD_AmbientParameters = 0x98;
    int TOD_SunParameters = 0x68;
    int TOD_CycleParameters = 0x40;
    int BaseMovement = 0x588;;
    int PlayerWalkMovement1 = 0x108;
    int PlayerWalkMovement2 = 0x100;
    int SkinnedMultiMesh = 0x278;
    int SkinnedRenderersList = 0x40;
    int materialsCount = 0x18;
    int Automatic = 0x2D8;
    int aimSway = 0x334;
    int hipAimCone = 0x3B0;
    int aimCone = 0x350;
    int stancePenaltyScale = 0x368;
    int aimConePenaltyMax = 0x35C;
    int aimconePenaltyPerShot = 0x358;
    int successFraction = 0x3F0;
};