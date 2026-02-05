#define _TYPES_CC_
#ifdef _TYPES_CC_

#include "types.h"

static const float TypeChart[TYPE_COUNT][TYPE_COUNT] = {
    /* DEFENSOR ->  NOR  FIR  WAT  ELE  GRA  ICE  FIG  POI  GRO  FLY  PSY  BUG  ROC  GHO  DRA  DAR  STE  FAI */
    /* NOR */     { NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NVE, IMM, NEU, NEU, NVE, NEU },
    /* FIR */     { NEU, NVE, NVE, NEU, SUP, SUP, NEU, NEU, NEU, NEU, NEU, SUP, NVE, NEU, NVE, NEU, SUP, NEU },
    /* WAT */     { NEU, SUP, NVE, NEU, NVE, NEU, NEU, NEU, SUP, NEU, NEU, NEU, SUP, NEU, NVE, NEU, NEU, NEU },
    /* ELE */     { NEU, NEU, SUP, NVE, NVE, NEU, NEU, NEU, IMM, SUP, NEU, NEU, NEU, NEU, NVE, NEU, NEU, NEU },
    /* GRA */     { NEU, NVE, SUP, NEU, NVE, NEU, NEU, NVE, SUP, NVE, NEU, NVE, SUP, NEU, NVE, NEU, NVE, NEU },
    /* ICE */     { NEU, NVE, NVE, NEU, SUP, NVE, NEU, NEU, SUP, SUP, NEU, NEU, NEU, NEU, SUP, NEU, NVE, NEU },
    /* FIG */     { SUP, NEU, NEU, NEU, NEU, SUP, NEU, NVE, NEU, NVE, NVE, NVE, SUP, IMM, NEU, SUP, SUP, NVE },
    /* POI */     { NEU, NEU, NEU, NEU, SUP, NEU, NEU, NVE, NVE, NEU, NEU, NEU, NVE, NVE, NEU, NEU, IMM, SUP },
    /* GRO */     { NEU, SUP, NEU, SUP, NVE, NEU, NEU, SUP, NEU, IMM, NEU, NVE, SUP, NEU, NEU, NEU, SUP, NEU },
    /* FLY */     { NEU, NEU, NEU, NVE, SUP, NEU, SUP, NEU, NEU, NEU, NEU, SUP, NVE, NEU, NEU, NEU, NVE, NEU },
    /* PSY */     { NEU, NEU, NEU, NEU, NEU, NEU, SUP, SUP, NEU, NEU, NVE, NEU, NEU, NEU, NEU, IMM, NVE, NEU },
    /* BUG */     { NEU, NVE, NEU, NEU, SUP, NEU, NVE, NVE, NEU, NVE, SUP, NEU, NEU, NVE, NEU, SUP, NVE, NVE },
    /* ROC */     { NEU, SUP, NEU, NEU, NEU, SUP, NVE, NEU, NVE, SUP, NEU, SUP, NEU, NEU, NEU, NEU, NVE, NEU },
    /* GHO */     { IMM, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, SUP, NEU, NEU, SUP, NEU, NVE, NEU, NEU },
    /* DRA */     { NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, SUP, NEU, NVE, IMM },
    /* DAR */     { NEU, NEU, NEU, NEU, NEU, NEU, NVE, NEU, NEU, NEU, SUP, NEU, NEU, SUP, NEU, NVE, NEU, NVE },
    /* STE */     { NEU, NVE, NVE, NVE, NEU, SUP, NEU, NEU, NEU, NEU, NEU, NEU, SUP, NEU, NEU, NEU, NVE, SUP },
    /* FAI */     { NEU, NVE, NEU, NEU, NEU, NEU, SUP, NVE, NEU, NEU, NEU, NEU, NEU, NEU, SUP, SUP, NVE, NEU }
};

float cl_Type::GetEffectivenessAgainst(cl_Type defender1, cl_Type defender2) {
    float multiplier1 = GetEffectivenessAgainst(defender1);

    float multiplier2 = 1.0f;
    
    if (defender2.type != TYPE_NONE && defender2.type != defender1.type) {
        multiplier2 = GetEffectivenessAgainst(defender2);
    }

    return multiplier1 * multiplier2;
}

float cl_Type::Attacking(cl_Type defender) {
    return GetEffectivenessAgainst(defender);
}

float cl_Type::Defending(cl_Type attacker) {
    return attacker.GetEffectivenessAgainst(*this);
}

#endif //_TYPES_CC_