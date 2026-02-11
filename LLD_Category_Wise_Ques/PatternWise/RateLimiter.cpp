#include <iostream>
#include <unordered_map>
#include <ctime>
#include <algorithm>

// 1. Base Strategy Interface
class RateLimitStrategy {
public:
    virtual ~RateLimitStrategy() {}
    virtual bool allowRequest() = 0;
};

// 2. Token Bucket Algorithm
class TokenBucket : public RateLimitStrategy {
private:
    long long capacity;      // Max tokens
    long long tokens;        // Current available tokens
    double refillRate;       // Tokens added per second
    long long lastRefillTime; // Timestamp of last refill (seconds)

public:
    TokenBucket(long long cap, double rate) 
        : capacity(cap), tokens(cap), refillRate(rate) {
        lastRefillTime = std::time(nullptr);
    }

    bool allowRequest() override {
        refill();
        if (tokens > 0) {
            tokens--;
            return true;
        }
        return false;
    }

private:
    void refill() {
        long long now = std::time(nullptr);
        long long timePassed = now - lastRefillTime;
        
        // Calculate new tokens based on time elapsed
        long long newTokens = (long long)(timePassed * refillRate);
        
        if (newTokens > 0) {
            tokens = std::min(capacity, tokens + newTokens);
            lastRefillTime = now;
        }
    }
};

// 3. Manager Class (LLD Context)
class RateLimiterManager {
private:
    std::unordered_map<std::string, RateLimitStrategy*> userBuckets;
    long long defaultCap;
    double defaultRate;

public:
    RateLimiterManager(long long cap, double rate) 
        : defaultCap(cap), defaultRate(rate) {}

    bool isAllowed(std::string userId) {
        // Create a bucket for the user if it doesn't exist
        if (userBuckets.find(userId) == userBuckets.end()) {
            userBuckets[userId] = new TokenBucket(defaultCap, defaultRate);
        }
        return userBuckets[userId]->allowRequest();
    }

    ~RateLimiterManager() {
        for (auto const& [id, bucket] : userBuckets) {
            delete bucket;
        }
    }
};

int main() {
    // Limit: 5 requests max burst, refills 1 token per second
    RateLimiterManager* limiter = new RateLimiterManager(5, 1.0);

    std::string user = "User_123";

    // Simulating rapid requests
    for (int i = 1; i <= 7; ++i) {
        if (limiter->isAllowed(user)) {
            std::cout << "Request " << i << ": [ALLOWED]\n";
        } else {
            std::cout << "Request " << i << ": [REJECTED] - Rate limit exceeded.\n";
        }
    }

    delete limiter;
    return 0;
}