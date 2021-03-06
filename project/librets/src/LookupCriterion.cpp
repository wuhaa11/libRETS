/*
 * Copyright (C) 2005 National Association of REALTORS(R)
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, and/or sell copies of the
 * Software, and to permit persons to whom the Software is furnished
 * to do so, provided that the above copyright notice(s) and this
 * permission notice appear in all copies of the Software and that
 * both the above copyright notice(s) and this permission notice
 * appear in supporting documentation.
 */

#include <iostream>
#include "librets/LookupCriterion.h"
#include "librets/AndCriterion.h"
#include "librets/OrCriterion.h"
#include "librets/util.h"

using namespace librets;
using namespace librets::util;
using std::string;
using std::ostream;
namespace b = boost;

LookupCriterion::LookupCriterion(string field)
    : mField(field), mCriteria()
{
}

string LookupCriterion::getField() const
{
    return mField;
}

void LookupCriterion::add(DmqlCriterionPtr criterion)
{
    /*
     * Take advantage of the associative law to merge like operations
     * into one operation:
     *
     *  (A + B) + C = A + (B + C) = A + B + C
     *  (A * B) * C = A * (B * C) = A * B * C
     */
    LookupCriterionPtr lookup =
        b::dynamic_pointer_cast<LookupCriterion>(criterion);
    if (lookup)
    {
        if (OperationName() == lookup->OperationName())
        {
            addAll(lookup);
        }
        else
        {
            mCriteria.push_back(criterion);
        }
    }
    else
    {
        mCriteria.push_back(criterion);
    }
}

void LookupCriterion::addAll(LookupCriterionPtr lookup)
{
    addAll(lookup->mCriteria);
}

void LookupCriterion::addAll(const CriterionList & criteria)
{
    CriterionList::const_iterator i;
    for (i = criteria.begin(); i != criteria.end(); i++)
    {
        mCriteria.push_back(*i);
    }
}

ostream & LookupCriterion::ToDmql(ostream & out) const
{
    out << "(" << mField << Operator();
    CriterionList::const_iterator i;
    string  separator = "";
    for (i = mCriteria.begin(); i != mCriteria.end(); i++)
    {
        out << separator;
        DmqlCriterionPtr criterion = *i;
        criterion->ToDmql(out);
        separator = ",";
    }
    return out << ")";
}

ostream & LookupCriterion::Print(ostream & outputStream) const
{
    return outputStream << "(<" << OperationName() << "> <"
        << mField << "> <" << Output(mCriteria) << ">)";
}

bool LookupCriterion::Equals(const RetsObject * object) const
{
    const LookupCriterion * rhs =
        dynamic_cast<const LookupCriterion *>(object);
    if (rhs == 0)
    {
        return false;
    }
    
    bool equals = true;
    equals &= (mField == rhs->mField);
    equals &= (OperationName() == rhs->OperationName());
    equals &= VectorEquals(mCriteria, rhs->mCriteria);
    return equals;
}
