//
//  SCFilterConstant.hpp
//
//  Created by rayyyhuang on 2021/7/6.
//

#ifndef SCFilterConstant_hpp
#define SCFilterConstant_hpp

#define SCFilterType_Copy "CopyFilter"
#define SCFilterType_Lut "LutFilter"
#define SCFilterType_BlurSub "BlurSubFilter"
#define SCFilterType_Blur "BlurFilter"
#define SCFilterType_Mix "MixFilter"
#define SCFilterType_Smooth "SmoothFilter"
#define SCFilterType_SharpenUSM "SharpenUSMFilter"
#define SCFilterType_Point "PointFilter"
#define SCFilterType_BackgroundPoint "BackgroundPointFilter"
#define SCFilterType_FacePoint "FacePointFilter"
#define SCFilterType_Line "LineFilter"
#define SCFilterType_BackgroundLine "BackgroundLineFilter"
#define SCFilterType_FaceLine "FaceLineFilter"
#define SCFilterType_Mesh "MeshFilter"
#define SCFilterType_BackgroundMesh "BackgroundMeshFilter"
#define SCFilterType_SmallHead "SmallHeadFilter"

#define SCFilterParam_Lut_Path SCFilterType_Lut "_Path"
#define SCFilterParam_Lut_Alpha SCFilterType_Lut "_Alpha"
#define SCFilterParam_Mix_Alpha SCFilterType_Mix "_Alpha"
#define SCFilterParam_Blur_Alpha SCFilterType_Blur "_Alpha"
#define SCFilterParam_Sharpen_Alpha SCFilterType_SharpenUSM "_SharpenAlpha"
#define SCFilterParam_SmallHead_Degree SCFilterType_SmallHead "_SmallHeadDegree"

#endif /* SCFilterConstant_hpp */
