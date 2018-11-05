/////////////////////////////////////////////////////////////////////////////
// Name:        attalternates.h
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_ATT_ALTERNATES_H__
#define __VRV_ATT_ALTERNATES_H__

#include <string>

//----------------------------------------------------------------------------

#include "vrvdef.h"

namespace vrv {

//----------------------------------------------------------------------------
// Alternate data types not generated by LibMEI
//----------------------------------------------------------------------------

/**
 * MEI data.COMPASSDIRECTION
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum CompassDirectionType { COMPASSDIRECTION_NONE = 0, COMPASSDIRECTION_basic, COMPASSDIRECTION_extended };

class data_COMPASSDIRECTION {
public:
    data_COMPASSDIRECTION() { Reset(COMPASSDIRECTION_NONE); }
    virtual ~data_COMPASSDIRECTION() {}

    void Reset(CompassDirectionType type)
    {
        m_type = type;
        m_basic = COMPASSDIRECTION_basic_NONE;
        m_extended = COMPASSDIRECTION_extended_NONE;
    }

    CompassDirectionType GetType() const { return m_type; }

    data_COMPASSDIRECTION_basic GetBasic() const { return m_basic; }
    void SetBasic(data_COMPASSDIRECTION_basic value)
    {
        Reset(COMPASSDIRECTION_basic);
        m_basic = value;
    }

    data_COMPASSDIRECTION_extended GetExtended() const { return m_extended; }
    void SetExtended(data_COMPASSDIRECTION_extended value)
    {
        Reset(COMPASSDIRECTION_extended);
        m_extended = value;
    }

    bool HasValue() const
    {
        if (m_basic != COMPASSDIRECTION_basic_NONE) return true;
        if (m_extended != COMPASSDIRECTION_extended_NONE) return true;
        return false;
    }

    // comparison
    bool operator==(const data_COMPASSDIRECTION &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_basic != val.GetBasic()) return false;
        if (m_extended != val.GetExtended()) return false;
        return true;
    }
    bool operator!=(const data_COMPASSDIRECTION &val) const { return !(*this == val); }

protected:
    CompassDirectionType m_type;
    data_COMPASSDIRECTION_basic m_basic;
    data_COMPASSDIRECTION_extended m_extended;
};
    
/**
 * MEI data.EVENTREL
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum EventRelType { EVENTREL_NONE = 0, EVENTREL_basic, EVENTREL_extended };

class data_EVENTREL {
public:
    data_EVENTREL() { Reset(EVENTREL_NONE); }
    virtual ~data_EVENTREL() {}

    void Reset(EventRelType type)
    {
        m_type = type;
        m_basic = EVENTREL_basic_NONE;
        m_extended = EVENTREL_extended_NONE;
    }

    EventRelType GetType() const { return m_type; }

    data_EVENTREL_basic GetBasic() const { return m_basic; }
    void SetBasic(data_EVENTREL_basic value)
    {
        Reset(EVENTREL_basic);
        m_basic = value;
    }

    data_EVENTREL_extended GetExtended() const { return m_extended; }
    void SetExtended(data_EVENTREL_extended value)
    {
        Reset(EVENTREL_extended);
        m_extended = value;
    }

    bool HasValue() const
    {
        if (m_basic != EVENTREL_basic_NONE) return true;
        if (m_extended != EVENTREL_extended_NONE) return true;
        return false;
    }

    // comparison
    bool operator==(const data_EVENTREL &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_basic != val.GetBasic()) return false;
        if (m_extended != val.GetExtended()) return false;
        return true;
    }
    bool operator!=(const data_EVENTREL &val) const { return !(*this == val); }

protected:
    EventRelType m_type;
    data_EVENTREL_basic m_basic;
    data_EVENTREL_extended m_extended;
};

/**
 * MEI data.FONTSIZE
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum FontSizeType { FONTSIZE_NONE = 0, FONTSIZE_fontSizeNumeric, FONTSIZE_term, FONTSIZE_percent };

class data_FONTSIZE {
public:
    data_FONTSIZE() { Reset(FONTSIZE_NONE); }
    virtual ~data_FONTSIZE() {}

    void Reset(FontSizeType type)
    {
        m_type = type;
        m_fontSizeNumeric = VRV_UNSET;
        m_term = FONTSIZETERM_NONE;
        m_percent = 0;
    }

    FontSizeType GetType() const { return m_type; }

    data_FONTSIZENUMERIC GetFontSizeNumeric() const { return m_fontSizeNumeric; }
    void SetFontSizeNumeric(data_FONTSIZENUMERIC value)
    {
        Reset(FONTSIZE_fontSizeNumeric);
        m_fontSizeNumeric = value;
    }

    data_FONTSIZETERM GetTerm() const { return m_term; }
    void SetTerm(data_FONTSIZETERM value)
    {
        Reset(FONTSIZE_term);
        m_term = value;
    }

    data_PERCENT GetPercent() const { return m_percent; }
    void SetPercent(data_PERCENT value)
    {
        Reset(FONTSIZE_percent);
        m_percent = value;
    }

    bool HasValue() const
    {
        if (m_fontSizeNumeric != VRV_UNSET) return true;
        if (m_term != FONTSIZETERM_NONE) return true;
        if (m_percent != 0) return true;
        return false;
    }

    // comparison
    bool operator==(const data_FONTSIZE &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_fontSizeNumeric != val.GetFontSizeNumeric()) return false;
        if (m_term != val.GetTerm()) return false;
        if (m_percent != val.GetPercent()) return false;
        return true;
    }
    bool operator!=(const data_FONTSIZE &val) const { return !(*this == val); }

protected:
    FontSizeType m_type;
    data_FONTSIZENUMERIC m_fontSizeNumeric;
    data_FONTSIZETERM m_term;
    data_PERCENT m_percent;
};

/**
 * MEI data.MIDIVALUE_NAME
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum MidivalueNameType { MIDIVALUENAMETYPE_NONE = 0, MIDIVALUENAMETYPE_midivalue, MIDIVALUENAMETYPE_mcname };

class data_MIDIVALUE_NAME {
public:
    data_MIDIVALUE_NAME() { Reset(MIDIVALUENAMETYPE_NONE); }
    virtual ~data_MIDIVALUE_NAME() {}

    void Reset(MidivalueNameType type)
    {
        m_type = type;
        m_midivalue = -1;
        m_ncname = "";
    }

    MidivalueNameType GetType() const { return m_type; }

    data_MIDIVALUE GetMidivalue() const { return m_midivalue; }
    void SetMidivalue(data_MIDIVALUE value)
    {
        Reset(MIDIVALUENAMETYPE_midivalue);
        m_midivalue = value;
    }

    data_NCNAME GetNcname() const { return m_ncname; }
    void SetNcname(data_NCNAME value)
    {
        Reset(MIDIVALUENAMETYPE_mcname);
        m_ncname = value;
    }

    bool HasValue() const
    {
        if (m_midivalue != -1) return true;
        if (m_ncname != "") return true;
        return false;
    }

    // comparison
    bool operator==(const data_MIDIVALUE_NAME &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_midivalue != val.GetMidivalue()) return false;
        if (m_ncname != val.GetNcname()) return false;
        return true;
    }
    bool operator!=(const data_MIDIVALUE_NAME &val) const { return !(*this == val); }

protected:
    MidivalueNameType m_type;
    data_MIDIVALUE m_midivalue;
    data_NCNAME m_ncname;
};

/**
 * MEI data.MIDIVALUE_PAN
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum MidivaluePanType { MIDIVALUEPANTYPE_NONE = 0, MIDIVALUEPANTYPE_midivalue, MIDIVALUEPANTYPE_percentLimitedSigned };

class data_MIDIVALUE_PAN {
public:
    data_MIDIVALUE_PAN() { Reset(MIDIVALUEPANTYPE_NONE); }
    virtual ~data_MIDIVALUE_PAN() {}

    void Reset(MidivaluePanType type)
    {
        m_type = type;
        m_midivalue = -1;
        m_percentLimitedSigned = VRV_UNSET;
    }

    MidivaluePanType GetType() const { return m_type; }

    data_MIDIVALUE GetMidivalue() const { return m_midivalue; }
    void SetMidivalue(data_MIDIVALUE value)
    {
        Reset(MIDIVALUEPANTYPE_midivalue);
        m_midivalue = value;
    }

    data_PERCENT_LIMITED_SIGNED GetPercentLimitedSigned() const { return m_percentLimitedSigned; }
    void SetPercentLimitedSigned(data_PERCENT_LIMITED_SIGNED value)
    {
        Reset(MIDIVALUEPANTYPE_percentLimitedSigned);
        m_percentLimitedSigned = value;
    }

    bool HasValue() const
    {
        if (m_midivalue != -1) return true;
        if (m_percentLimitedSigned != VRV_UNSET) return true;
        return false;
    }

    // comparison
    bool operator==(const data_MIDIVALUE_PAN &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_midivalue != val.GetMidivalue()) return false;
        if (m_percentLimitedSigned != val.GetPercentLimitedSigned()) return false;
        return true;
    }
    bool operator!=(const data_MIDIVALUE_PAN &val) const { return !(*this == val); }

protected:
    MidivaluePanType m_type;
    data_MIDIVALUE m_midivalue;
    data_PERCENT_LIMITED_SIGNED m_percentLimitedSigned;
};

/**
 * MEI data.STAFFITEM
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum StaffItemType { STAFFITEM_NONE = 0, STAFFITEM_basic, STAFFITEM_cmn, STAFFITEM_mensural };

class data_STAFFITEM {
public:
    data_STAFFITEM() { Reset(STAFFITEM_NONE); }
    virtual ~data_STAFFITEM() {}

    void Reset(StaffItemType type)
    {
        m_type = type;
        m_basic = STAFFITEM_basic_NONE;
        m_cmn = STAFFITEM_cmn_NONE;
        m_mensural = STAFFITEM_mensural_NONE;
    }

    StaffItemType GetType() const { return m_type; }

    data_STAFFITEM_basic GetBasic() const { return m_basic; }
    void SetBasic(data_STAFFITEM_basic value)
    {
        Reset(STAFFITEM_basic);
        m_basic = value;
    }

    data_STAFFITEM_cmn GetCmn() const { return m_cmn; }
    void SetCmn(data_STAFFITEM_cmn value)
    {
        Reset(STAFFITEM_cmn);
        m_cmn = value;
    }

    data_STAFFITEM_mensural GetMensural() const { return m_mensural; }
    void SetMensural(data_STAFFITEM_mensural value)
    {
        Reset(STAFFITEM_mensural);
        m_mensural = value;
    }

    bool HasValue() const
    {
        if (m_basic != STAFFITEM_basic_NONE) return true;
        if (m_cmn != STAFFITEM_cmn_NONE) return true;
        if (m_mensural != STAFFITEM_mensural_NONE) return true;
        return false;
    }

    // comparison
    bool operator==(const data_STAFFITEM &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_basic != val.GetBasic()) return false;
        if (m_cmn != val.GetCmn()) return false;
        if (m_mensural != val.GetMensural()) return false;
        return true;
    }
    bool operator!=(const data_STAFFITEM &val) const { return !(*this == val); }

protected:
    StaffItemType m_type;
    data_STAFFITEM_basic m_basic;
    data_STAFFITEM_cmn m_cmn;
    data_STAFFITEM_mensural m_mensural;
};

/**
 * MEI data.STAFFREL
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum StaffRelType { STAFFREL_NONE = 0, STAFFREL_basic, STAFFREL_extended };

class data_STAFFREL {
public:
    data_STAFFREL() { Reset(STAFFREL_NONE); }
    virtual ~data_STAFFREL() {}

    void Reset(StaffRelType type)
    {
        m_type = type;
        m_basic = STAFFREL_basic_NONE;
        m_extended = STAFFREL_extended_NONE;
    }

    StaffRelType GetType() const { return m_type; }

    data_STAFFREL_basic GetBasic() const { return m_basic; }
    void SetBasic(data_STAFFREL_basic value)
    {
        Reset(STAFFREL_basic);
        m_basic = value;
    }

    data_STAFFREL_extended GetExtended() const { return m_extended; }
    void SetExtended(data_STAFFREL_extended value)
    {
        Reset(STAFFREL_extended);
        m_extended = value;
    }

    bool HasValue() const
    {
        if (m_basic != STAFFREL_basic_NONE) return true;
        if (m_extended != STAFFREL_extended_NONE) return true;
        return false;
    }

    // comparison
    bool operator==(const data_STAFFREL &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_basic != val.GetBasic()) return false;
        if (m_extended != val.GetExtended()) return false;
        return true;
    }
    bool operator!=(const data_STAFFREL &val) const { return !(*this == val); }

protected:
    StaffRelType m_type;
    data_STAFFREL_basic m_basic;
    data_STAFFREL_extended m_extended;
};

//----------------------------------------------------------------------------
// Alternate data types unsing other alternate data types (above)
//----------------------------------------------------------------------------

/**
 * MEI data.PLACEMENT
 * Since it can contain different subtype we need a dedicated class for it.
 */

enum PlacementType { PLACEMENT_NONE = 0, PLACEMENT_staffRel, PLACEMENT_nonStaffPlace, PLACEMENT_nmtoken };

class data_PLACEMENT {
public:
    data_PLACEMENT() { Reset(PLACEMENT_NONE); }
    virtual ~data_PLACEMENT() {}

    void Reset(PlacementType type)
    {
        m_type = type;
        m_staffRel = data_STAFFREL();
        m_nonStaffPlace = NONSTAFFPLACE_NONE;
        m_nmtoken = "";
    }

    PlacementType GetType() const { return m_type; }

    data_STAFFREL GetStaffRel() const { return m_staffRel; }
    void SetStaffRel(data_STAFFREL value)
    {
        Reset(PLACEMENT_staffRel);
        m_staffRel = value;
    }
    data_STAFFREL *GetStaffRelAtlernate() { return &m_staffRel; }

    data_NONSTAFFPLACE GetNonStaffPlace() const { return m_nonStaffPlace; }
    void SetNonStaffPlace(data_NONSTAFFPLACE value)
    {
        Reset(PLACEMENT_nonStaffPlace);
        m_nonStaffPlace = value;
    }

    std::string GetNMToken() const { return m_nmtoken; }
    void SetNMToken(std::string value)
    {
        Reset(PLACEMENT_nmtoken);
        m_nmtoken = value;
    }

    bool HasValue() const
    {
        if (m_staffRel.HasValue()) return true;
        if (m_nonStaffPlace != NONSTAFFPLACE_NONE) return true;
        if (m_nmtoken != "") return true;
        return false;
    }

    // comparison
    bool operator==(const data_PLACEMENT &val) const
    {
        if (m_type != val.GetType()) return false;
        if (m_staffRel != val.GetStaffRel()) return false;
        if (m_nonStaffPlace != val.GetNonStaffPlace()) return false;
        if (m_nmtoken != val.GetNMToken()) return false;
        return true;
    }
    bool operator!=(const data_PLACEMENT &val) const { return !(*this == val); }

protected:
    PlacementType m_type;
    data_STAFFREL m_staffRel;
    data_NONSTAFFPLACE m_nonStaffPlace;
    std::string m_nmtoken;
};

} // namespace vrv

#endif
