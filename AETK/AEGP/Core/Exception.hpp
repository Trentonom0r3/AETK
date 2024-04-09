/*****************************************************************/ /**
                                                                     * \file   Exception.hpp
                                                                     * \brief  A custom exception class derived from
                                                                     *std::exception, for managing AE exceptions. Also
                                                                     *includes a utility function for null checking.
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   March 2024
                                                                     *********************************************************************/

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @class AEException
 * @brief A custom exception class derived from std::exception.
 *
 * This class represents an exception that can be thrown in the project. It
 * provides a way to encapsulate and propagate error messages.
 */
class AEException : public std::exception
{
  public:
    /**
     * @brief Constructs an AEException object with the given error message.
     *
     * @param message The error message associated with the exception.
     */
    AEException(const std::string &message) : m_message(message) {}

    /**
     * @brief Constructs an AEException object with the given error message.
     *
     * @param message The error message associated with the exception.
     */
    AEException(const char *message) : m_message(message) {}

    /**
     * @brief Returns the error message associated with the exception.
     *
     * @return const char* The error message.
     */
    virtual const char *what() const throw() { return m_message.c_str(); }

  private:
    std::string m_message;
};

/**
 * @brief Utility function for null checking.
 *
 * This function checks if a pointer is null and throws an AEException if it is.
 *
 * @tparam T The type of the pointer.
 * @param ptr The pointer to check.
 * @param errorMessage The error message to be associated with the exception.
 */
template <typename T> void CheckNotNull(T *ptr, const char *errorMessage)
{
    if (ptr == nullptr)
    {
        throw AEException(errorMessage);
    }
}

#endif // EXCEPTION_HPP