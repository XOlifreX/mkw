#include "CourseCheckpoints.hpp"

// --- EXTERN DECLARATIONS BEGIN ---

extern "C" {

// Extern function references.
// PAL: 0x8002157c
extern UNKNOWN_FUNCTION(_savegpr_18);
// PAL: 0x8002158c
extern UNKNOWN_FUNCTION(_savegpr_22);
// PAL: 0x80021590
extern UNKNOWN_FUNCTION(_savegpr_23);
// PAL: 0x800215c8
extern UNKNOWN_FUNCTION(_restgpr_18);
// PAL: 0x800215d8
extern UNKNOWN_FUNCTION(_restgpr_22);
// PAL: 0x800215dc
extern UNKNOWN_FUNCTION(_restgpr_23);
// PAL: 0x80229e14
extern UNKNOWN_FUNCTION(checkSectorAndDistanceRatio__Q26System17MapdataCheckPointCFRCQ23EGG8Vector3fPf);
// PAL: 0x80511110
extern UNKNOWN_FUNCTION(KmpHolder_findNextCheckpointRec);
// PAL: 0x80511ec8
extern UNKNOWN_FUNCTION(computeExactFinishingTimeInner);
// PAL: 0x8051201c
extern UNKNOWN_FUNCTION(VEC2_sub);
// PAL: 0x80512040
extern UNKNOWN_FUNCTION(VEC2_add);
// PAL: 0x80512064
extern UNKNOWN_FUNCTION(unk_80512064);
// PAL: 0x80515c24
extern UNKNOWN_FUNCTION(
    getCheckPoint__Q26System9CourseMapCFUs); // Extern data references.
// PAL: 0x80386000
extern UNKNOWN_DATA(sInstance__Q26System13SystemManager);
}

// --- EXTERN DECLARATIONS END ---

// .rodata
extern "C" UNKNOWN_DATA(lbl_8088f8d0);
REL_SYMBOL_AT(lbl_8088f8d0, 0x8088f8d0)

extern "C" UNKNOWN_DATA(lbl_8088f8d4);
REL_SYMBOL_AT(lbl_8088f8d4, 0x8088f8d4)

// .data

// .bss

// Symbol: checkSector__Q26System17MapdataCheckPointCFRCQ26System16LinkedCheckpointRCQ23EGG8Vector2fRCQ23EGG8Vector2f
namespace System {
bool MapdataCheckPoint::checkSector(const LinkedCheckpoint& next,
                                    const EGG::Vector2f& p0,
                                    const EGG::Vector2f& p1) const {
  if (-(next.p0diff.y) * p0.x + next.p0diff.x * p0.y < 0.0f)
    return false;

  if (next.p1diff.y * p1.x - next.p1diff.x * p1.y < 0.0f)
    return false;

  return true;
}

bool MapdataCheckPoint::checkDistanceRatio(const LinkedCheckpoint& next, 
                                           const EGG::Vector2f& p0,
                                           const EGG::Vector2f& p1, 
                                           f32* distanceRatio) const {
  float dot = this->mDir.dot(p1);
  float dot2 = -(next.checkpoint->mDir.dot(p0));
  float ratio = (dot) / (dot + dot2);
  
  *distanceRatio = ratio;
  
  return (ratio >= 0.0f) && (ratio <= 1.0f);
}

MapdataCheckPoint::Completion MapdataCheckPoint::checkSectorAndDistanceRatio_(
    const LinkedCheckpoint& next,
    const EGG::Vector2f& p0,
    const EGG::Vector2f& p1,
    f32* distanceRatio) const
{   
    if (!this->checkSector(next, p0, p1))
        return Completion_1;
    
    if (!this->checkDistanceRatio(next, p0, p1, distanceRatio))
        return Completion_2;

    return Completion_0;
}

MapdataCheckPoint::Completion MapdataCheckPoint::checkSectorAndDistanceRatio(
    const EGG::Vector3f& pos,
    f32* distanceRatio) const
{   
    EGG::Vector2f temp1((this->mpData->right).x, (this->mpData->right).y);
    temp1.y = pos.z - temp1.y;
    temp1.x = pos.x - temp1.x;
 
    bool isCompletion2 = false;
    for (int i = 0; i < this->mNextCount; i++) {
        EGG::Vector2f temp2((this->mNextPoints[i].checkpoint->mpData->left).x, (this->mNextPoints[i].checkpoint->mpData->left).y);
        temp2.y = pos.z - temp2.y;
        temp2.x = pos.x - temp2.x;

        switch(this->checkSectorAndDistanceRatio_(this->mNextPoints[i], temp2, temp1, distanceRatio)) {
            case Completion_0: 
                return Completion_0;
            case Completion_2: 
                isCompletion2 = true;
                break;
        }
    }

    return isCompletion2 ? Completion_2 : Completion_1;
}
} // namespace System

const u32 lbl_8088f8d8[] = {0x3f000000, 0x00000000};
const u32 lbl_8088f8e0[] = {0x43300000, 0x00000000};

// Symbol: unk_80510f18
// PAL: 0x80510f18..0x80510f58
MARK_BINARY_BLOB(unk_80510f18, 0x80510f18, 0x80510f58);
asm UNKNOWN_FUNCTION(unk_80510f18){
#include "asm/80510f18.s"
}

// Symbol: unk_80510f58
// PAL: 0x80510f58..0x80511034
MARK_BINARY_BLOB(unk_80510f58, 0x80510f58, 0x80511034);
asm UNKNOWN_FUNCTION(unk_80510f58){
#include "asm/80510f58.s"
}

// Symbol: unk_80511034
// PAL: 0x80511034..0x80511110
MARK_BINARY_BLOB(unk_80511034, 0x80511034, 0x80511110);
asm UNKNOWN_FUNCTION(unk_80511034){
#include "asm/80511034.s"
}

// Symbol: KmpHolder_findNextCheckpointRec
// PAL: 0x80511110..0x80511500
MARK_BINARY_BLOB(KmpHolder_findNextCheckpointRec, 0x80511110, 0x80511500);
asm UNKNOWN_FUNCTION(KmpHolder_findNextCheckpointRec){
#include "asm/80511110.s"
}

// Symbol: KmpHolder_findNextCheckpoint
// PAL: 0x80511500..0x80511e00
MARK_BINARY_BLOB(KmpHolder_findNextCheckpoint, 0x80511500, 0x80511e00);
asm UNKNOWN_FUNCTION(KmpHolder_findNextCheckpoint){
#include "asm/80511500.s"
}

// Symbol: unk_80511e00
// PAL: 0x80511e00..0x80511e7c
MARK_BINARY_BLOB(unk_80511e00, 0x80511e00, 0x80511e7c);
asm UNKNOWN_FUNCTION(unk_80511e00){
#include "asm/80511e00.s"
}

// Symbol: computeExactFinishingTime
// PAL: 0x80511e7c..0x80511ec8
MARK_BINARY_BLOB(computeExactFinishingTime, 0x80511e7c, 0x80511ec8);
asm UNKNOWN_FUNCTION(computeExactFinishingTime){
#include "asm/80511e7c.s"
}

// Symbol: computeExactFinishingTimeInner
// PAL: 0x80511ec8..0x8051201c
MARK_BINARY_BLOB(computeExactFinishingTimeInner, 0x80511ec8, 0x8051201c);
asm UNKNOWN_FUNCTION(computeExactFinishingTimeInner){
#include "asm/80511ec8.s"
}

// Symbol: VEC2_sub
// PAL: 0x8051201c..0x80512040
MARK_BINARY_BLOB(VEC2_sub, 0x8051201c, 0x80512040);
asm UNKNOWN_FUNCTION(VEC2_sub){
#include "asm/8051201c.s"
}

// Symbol: VEC2_add
// PAL: 0x80512040..0x80512064
MARK_BINARY_BLOB(VEC2_add, 0x80512040, 0x80512064);
asm UNKNOWN_FUNCTION(VEC2_add){
#include "asm/80512040.s"
}

// Symbol: unk_80512064
// PAL: 0x80512064..0x80512370
MARK_BINARY_BLOB(unk_80512064, 0x80512064, 0x80512370);
asm UNKNOWN_FUNCTION(unk_80512064){
#include "asm/80512064.s"
}

// Symbol: CheckpointHolder_computeMeanTotalDistance
// PAL: 0x80512370..0x80512694
MARK_BINARY_BLOB(CheckpointHolder_computeMeanTotalDistance, 0x80512370,
                 0x80512694);
asm UNKNOWN_FUNCTION(CheckpointHolder_computeMeanTotalDistance) {
#include "asm/80512370.s"
}