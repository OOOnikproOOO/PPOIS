/**
 * @file UserAccount.cpp
 * @brief Implementation of UserAccount methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "UserAccount.h"
#include "ComputerException.h"

UserAccount::UserAccount(const std::string& username, const std::string& role, bool is_logged_in, const std::string& password) :
    username_(username), role_(role), is_logged_in_(is_logged_in), failed_login_attempts_(0), password_(password) {}

bool UserAccount::operator==(const UserAccount& other) const {
    return username_ == other.username_ && role_ == other.role_ &&
           is_logged_in_ == other.is_logged_in_ && failed_login_attempts_ == other.failed_login_attempts_ &&
           password_ == other.password_;
}

bool UserAccount::operator!=(const UserAccount& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const UserAccount& account) {
    os << "UserAccount ['" << account.username_ << "' (" << account.role_ << "), Session: " << (account.is_logged_in_ ? "Logged In" : "Logged Out") << "]";
    return os;
}

bool UserAccount::Login(const std::string& password) {
    if (password == password_) {
        is_logged_in_ = true;
        failed_login_attempts_ = 0;
        return true;
    }
    failed_login_attempts_++;
    if (failed_login_attempts_ >= 3) 
        throw ComputerException("Account locked: Too many consecutive failed login attempts.");
    return false;
}

void UserAccount::Logout() {
    is_logged_in_ = false;
}

void UserAccount::ChangePassword(const std::string& old_password, const std::string& new_password) {
    if (old_password != password_) 
        throw ComputerException("Current password verification failed.");
    if (new_password.length() < 3) 
        throw ComputerException("New password must be at least 3 characters long.");
    password_ = new_password;
}

void UserAccount::ResetAttempts() {
    failed_login_attempts_ = 0;
}

const std::string& UserAccount::GetUsername() const {
    return username_;
}

void UserAccount::SetUsername(const std::string& username) {
    if (username.empty()) 
        throw ComputerException("Username cannot be empty.");
    username_ = username;
}

const std::string& UserAccount::GetRole() const {
    return role_;
}

bool UserAccount::IsLoggedIn() const {
    return is_logged_in_;
}

int UserAccount::GetFailedLoginAttempts() const {
    return failed_login_attempts_;
}