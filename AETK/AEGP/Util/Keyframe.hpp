/*****************************************************************/ /**
                                                                     * \file   Keyframe.hpp
                                                                     * \brief  A keyframe for the animation
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/
#ifndef KEYFRAME_HPP
#define KEYFRAME_HPP

#include "AETK/AEGP/Core/Types.hpp"

/**
 * @class KeyFrame
 * @brief Represents a keyframe in After Effects.
 *
 * Allows for the creation and manipulation of keyframes, including setting
 * their time, value, interpolation type, flags, easing, and tangents.
 */
class KeyFrame
{
  public:
    // Using std::variant to accommodate different tangent types.
    using TangentValue = std::variant<std::monostate, double, TwoDVal, ThreeDVal, ColorVal>;
    double time;
    TangentValue value = std::monostate(); // Value of the keyframe

    std::optional<std::pair<KeyInterp, KeyInterp>> interp; // Interpolation for in/out
    tk::vector<KeyframeFlag> flags = {};                   // Flags for the keyframe
    std::optional<KeyframeEase> easeIn,
        easeOut;                                         // Ease in/out values (std::tuple<double,double>)
    std::optional<std::pair<TangentValue, TangentValue>> // In/out
        tangents;                                        // Pair of in/out tangents

    KeyFrame(double time) : time(time) {}
    KeyFrame(double time, TangentValue value) : time(time), value(value){};
    KeyFrame &setInterpolation(KeyInterp inInterp, KeyInterp outInterp)
    {
        interp.emplace(std::make_pair(inInterp, outInterp));
        return *this;
    }

    KeyFrame &setEaseIn(double speed, double influence)
    {
        easeIn.emplace(KeyframeEase{speed, influence});
        return *this;
    }

    KeyFrame &setEaseOut(double speed, double influence)
    {
        easeOut.emplace(KeyframeEase{speed, influence});
        return *this;
    }

    KeyFrame &setFlag(KeyframeFlag keyframeFlags)
    {
        flags.push_back(keyframeFlags);
        return *this;
    }

    // Templated method to set tangents with type checking at compile time
    template <typename T> KeyFrame &setTangents(T inTan, T outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(double inTan, double outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(TwoDVal inTan, TwoDVal outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(ThreeDVal inTan, ThreeDVal outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(ColorVal inTan, ColorVal outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setValue(double value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(KeyFrame::TangentValue value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(TwoDVal value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(ThreeDVal value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(ColorVal value)
    {
        this->value = value;
        return *this;
    }

    std::string toString() const
    {
        std::ostringstream os;

        // Time
        os << "Time: " << time << "\n";

        // Value
        os << "Value: ";
        std::visit(
            overloaded{[&](double val) { os << val; },
                       [&](const TwoDVal &val) { os << "(" << val.x << ", " << val.y << ")"; },
                       [&](const ThreeDVal &val) { os << "(" << val.x << ", " << val.y << ", " << val.z << ")"; },
                       [&](const ColorVal &val) {
                           os << "(" << val.red << ", " << val.green << ", " << val.blue << ", " << val.alpha << ")";
                       },
                       [&](std::monostate) { os << "none"; }},
            value);
        os << "\n";

        // Interpolation
        if (interp.has_value())
        {
            os << "Interpolation: In - " << toInterpString(std::get<0>(interp.value())) << ", Out - "
               << toInterpString(std::get<1>(interp.value())) << "\n";
        }

        // Flags
        if (!flags.empty())
        {
            os << "Flags: ";
            for (auto &flag : flags)
            {
                os << toFlagString(flag) << " ";
            }
            os << "\n";
        }

        // Ease In/Out
        if (easeIn.has_value())
        {
            os << "Ease In: Speed - " << easeIn->speedF << ", Influence - " << easeIn->influenceF << "\n";
        }
        if (easeOut.has_value())
        {
            os << "Ease Out: Speed - " << easeOut->speedF << ", Influence - " << easeOut->influenceF << "\n";
        }

        // Tangents
        if (tangents.has_value())
        {
            os << "Tangents: In - ";
            std::visit(
                [&os](const auto &val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, double>)
                    {
                        os << val;
                    }
                    else if constexpr (std::is_same_v<T, TwoDVal>)
                    {
                        os << "(" << val.x << ", " << val.y << ")";
                    }
                    else if constexpr (std::is_same_v<T, ThreeDVal>)
                    {
                        os << "(" << val.x << ", " << val.y << ", " << val.z << ")";
                    }
                    else if constexpr (std::is_same_v<T, ColorVal>)
                    {
                        os << "(" << val.red << ", " << val.green << ", " << val.blue << ", " << val.alpha << ")";
                    }
                },
                tangents.value().first);

            os << ", Out - ";
            std::visit(
                [&os](const auto &val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, double>)
                    {
                        os << val;
                    }
                    else if constexpr (std::is_same_v<T, TwoDVal>)
                    {
                        os << "(" << val.x << ", " << val.y << ")";
                    }
                    else if constexpr (std::is_same_v<T, ThreeDVal>)
                    {
                        os << "(" << val.x << ", " << val.y << ", " << val.z << ")";
                    }
                    else if constexpr (std::is_same_v<T, ColorVal>)
                    {
                        os << "(" << val.red << ", " << val.green << ", " << val.blue << ", " << val.alpha << ")";
                    }
                },
                tangents.value().second);
            os << "\n";
        }

        return os.str();
    }

  private:
    std::string toInterpString(KeyInterp interp) const
    {
        switch (interp)
        {
        case KeyInterp::LINEAR:
            return "Linear";
        case KeyInterp::BEZIER:
            return "Bezier";
        case KeyInterp::HOLD:
            return "Hold";
        default:
            return "None";
        }
    }

    std::string toFlagString(KeyframeFlag flag) const
    {
        switch (flag)
        {
        case KeyframeFlag::TEMPORAL_CONTINUOUS:
            return "Temporal Continuous";
        case KeyframeFlag::TEMPORAL_AUTOBEZIER:
            return "Temporal AutoBezier";
        case KeyframeFlag::SPATIAL_CONTINUOUS:
            return "Spatial Continuous";
        case KeyframeFlag::SPATIAL_AUTOBEZIER:
            return "Spatial AutoBezier";
        case KeyframeFlag::ROVING:
            return "Roving";
        default:
            return "None";
        }
    }
};

#endif
// KEYFRAME_HPP