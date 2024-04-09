/*****************************************************************/ /**
                                                                     * \file   Context.hpp
                                                                     * \brief  File Containing Scoped "Context Managers"
                                                                     * Currently only supports Scoped_Undo_Guard and
                                                                     *Scoped_Quiet_Guard, for scoping Undo Groups and
                                                                     *Quiet Mode for error messages.
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   March 2024
                                                                     *********************************************************************/

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "AETK/AEGP/Core/Core.hpp"

/**
 * @brief Scoped_Undo_Guard is a class that is used to start and end an undo
 * group
 *
 * The Scoped_Undo_Guard class is used to manage the scoping of an undo group.
 * It provides a convenient way to start and end an undo group by automatically
 * calling the corresponding functions from the UtilitySuite6 class.
 *
 * @example
 * void someFunction() {
 * {<---- start of scope
 * Scoped_Undo_Guard guard("someFunction");
 * // do some stuff
 * }<---- end of scope, undo group is ended automatically
 */
class Scoped_Undo_Guard
{
  public:
    /**
     * Constructs a Scoped_Undo_Guard object with the specified name.
     *
     * @param name The name of the undo group.
     */
    Scoped_Undo_Guard(std::string name) { UtilitySuite().startUndoGroup(name); }

    /**
     * Destructs the Scoped_Undo_Guard object and ends the undo group.
     */
    ~Scoped_Undo_Guard() { UtilitySuite().endUndoGroup(); }
};

/**
 * @brief Scoped_Quiet_Guard is a class that is used to quiet error messages
 *
 * The Scoped_Quiet_Guard class is used to manage the scoping of quiet mode for
 * error messages. It provides a convenient way to start and end quiet mode by
 * automatically calling the corresponding functions from the UtilitySuite6
 * class.
 *
 * @example
 * void someFunction() {
 * {<---- start of scope
 * Scoped_Quiet_Guard guard;
 * // do some stuff
 * }<---- end of scope, quiet mode is ended automatically
 */
class Scoped_Quiet_Guard
{
  public:
    /**
     * Constructs a Scoped_Quiet_Guard object and starts quiet mode for error
     * messages.
     */
    Scoped_Quiet_Guard() { UtilitySuite().startQuietErrors(); }

    /**
     * Destructs the Scoped_Quiet_Guard object and ends quiet mode for error
     * messages.
     */
    ~Scoped_Quiet_Guard() { UtilitySuite().endQuietErrors(false); }
};
/**
 * @class Scoped_Error_Reporter
 *
 * @brief A class that reports errors caught within its scope.
 *
 * The Scoped_Error_Reporter class is responsible for catching and reporting
 * errors that occur within its scope. It provides a mechanism to re-throw
 * exceptions and handle them appropriately. If an exception is caught, it can
 * be reported as a standard or non-standard exception.
 */
class Scoped_Error_Reporter
{
  public:
    /**
     * @brief Default constructor for the Scoped_Error_Reporter class.
     */
    Scoped_Error_Reporter() = default;

    /**
     * @brief Destructor for the Scoped_Error_Reporter class.
     *
     * The destructor attempts to re-throw any exception caught during the scope
     * of this object. If an exception is caught, it is handled by reporting the
     * error message. If no exception is caught, the destructor does nothing. If
     * an error occurs while handling the exception, an optional catch block
     * logs the error or takes other appropriate actions.
     */
    ~Scoped_Error_Reporter()
    {
        try
        {
            // Attempt to re-throw any exception caught during the scope of this
            // object
            if (std::current_exception())
            { // Checks if there's an active exception
                try
                {
                    throw; // Re-throws the caught exception to handle it
                }
                catch (const AEException &e)
                {
                    // Handle AEGP exceptions by reporting the error message
                    ReportError(e.what());
                }
                catch (const std::exception &e)
                {
                    // Handle standard exceptions by reporting the error message
                    ReportError(e.what());
                }
                catch (...)
                {
                    // Handle non-standard exceptions by reporting an unknown
                    // error message
                    ReportError("An unknown error occurred.");
                }
            }
        }
        catch (...)
        {
            ReportError("An error occurred while handling an exception.");
        }
    }

  private:
    /**
     * @brief Reports an error message.
     *
     * This function reports an error message by calling the reportInfoUnicode
     * function of the UtilitySuite6 class.
     *
     * @param errorMessage The error message to be reported.
     */
    inline void ReportError(const std::string &errorMessage) { UtilitySuite().reportInfo(errorMessage); }
};



#endif // CONTEXT_HPP