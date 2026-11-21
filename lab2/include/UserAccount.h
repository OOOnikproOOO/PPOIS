/**
 * @file UserAccount.h
 * @brief Declaration of the UserAccount class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <iostream>
#include <string>

/**
 * @brief Represents a user identity account managing authentication and permissions.
 */
class UserAccount {
public:
    /**
     * @brief Constructs a UserAccount instance.
     * @param username Account identifier name.
     * @param role User privileges role ("Administrator" or "StandardUser").
     * @param is_logged_in Whether session is currently authenticated.
     * @param password Password credential string.
     */
    explicit UserAccount(const std::string& username = "OOOnikproOOO", const std::string& role = "Administrator", bool is_logged_in = false, const std::string& password = "OSTIS");

    /**
     * @brief Equality operator comparing account credentials and states.
     * @param other Another UserAccount instance.
     * @return true if accounts match.
     */
    bool operator==(const UserAccount& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another UserAccount instance.
     * @return true if accounts differ.
     */
    bool operator!=(const UserAccount& other) const;

    /**
     * @brief Stream output operator for formatting user account info.
     * @param os Output stream.
     * @param account UserAccount instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const UserAccount& account);

    /**
     * @brief Authenticates session using password credential.
     * @param password Password to verify.
     * @return true if authentication succeeds.
     */
    bool Login(const std::string& password);

    /**
     * @brief Logs out of active session.
     */
    void Logout();

    /**
     * @brief Updates account password credential.
     * @param old_password Previous password verification.
     * @param new_password New password string.
     */
    void ChangePassword(const std::string& old_password, const std::string& new_password);

    /**
     * @brief Resets counter of failed login attempts, unlocking the account.
     */
    void ResetAttempts();

    /**
     * @brief Gets account username.
     * @return Username string.
     */
    const std::string& GetUsername() const;

    /**
     * @brief Sets account username identifier.
     * @param username New username string.
     */
    void SetUsername(const std::string& username);

    /**
     * @brief Gets privilege role string.
     * @return Role name.
     */
    const std::string& GetRole() const;

    /**
     * @brief Checks whether session is currently active.
     * @return true if logged in.
     */
    bool IsLoggedIn() const;

    /**
     * @brief Gets count of consecutive failed login attempts.
     * @return Failed attempt counter.
     */
    int GetFailedLoginAttempts() const;

private:
    std::string username_;
    std::string role_;
    bool is_logged_in_;
    int failed_login_attempts_;
    std::string password_;
};

#endif