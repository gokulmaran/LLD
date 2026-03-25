#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// ======================= MESSAGE =======================

class Message {
    string payload;

public:
    Message(const string& payload) : payload(payload) {}

    string getPayload() const {
        return payload;
    }
};

// ======================= SUBSCRIBER =======================

class Subscriber {
public:
    virtual ~Subscriber() {}
    virtual void consume(const Message& message) = 0;
};

// ======================= CONCRETE SUBSCRIBER =======================

class EmailSubscriber : public Subscriber {
    string name;

public:
    EmailSubscriber(const string& name) : name(name) {}

    void consume(const Message& message) override {
        cout << "[SUBSCRIBER: " << name << "] Received message: "
             << message.getPayload() << endl;
    }
};

// ======================= TOPIC =======================

class Topic {
    string name;
    vector<Subscriber*> subscribers;

public:
    Topic(const string& name) : name(name) {}

    string getName() const {
        return name;
    }

    void addSubscriber(Subscriber* sub) {
        cout << "[TOPIC: " << name << "] Subscriber added\n";
        subscribers.push_back(sub);
    }

    void publish(const Message& message) {
        cout << "[TOPIC: " << name << "] Publishing message to "
             << subscribers.size() << " subscribers\n";

        for (auto* sub : subscribers) {
            sub->consume(message);
        }
    }
};

// ======================= BROKER =======================

class PubSubBroker {
    unordered_map<string, Topic*> topics;

public:
    ~PubSubBroker() {
        for (auto& pair : topics) {
            delete pair.second;
        }
    }

    Topic* getOrCreateTopic(const string& topicName) {
        if (topics.find(topicName) == topics.end()) {
            cout << "[BROKER] Creating topic: " << topicName << endl;
            topics[topicName] = new Topic(topicName);
        }
        return topics[topicName];
    }

    void subscribe(const string& topicName, Subscriber* subscriber) {
        Topic* topic = getOrCreateTopic(topicName);
        topic->addSubscriber(subscriber);
    }

    void publish(const string& topicName, const Message& message) {
        if (topics.find(topicName) == topics.end()) {
            cout << "[BROKER] No subscribers for topic: " << topicName << endl;
            return;
        }
        topics[topicName]->publish(message);
    }
};

// ======================= PUBLISHER =======================

class Publisher {
    PubSubBroker* broker;

public:
    Publisher(PubSubBroker* broker) : broker(broker) {}

    void publish(const string& topic, const string& payload) {
        cout << "[PUBLISHER] Publishing to topic: " << topic << endl;
        broker->publish(topic, Message(payload));
    }
};

// ======================= MAIN =======================

int main() {
    PubSubBroker broker;

    // Subscribers
    Subscriber* user1 = new EmailSubscriber("User-1");
    Subscriber* user2 = new EmailSubscriber("User-2");
    Subscriber* user3 = new EmailSubscriber("User-3");

    // Subscriptions
    broker.subscribe("OrderCreated", user1);
    broker.subscribe("OrderCreated", user2);
    broker.subscribe("PaymentSuccess", user3);

    // Publisher
    Publisher publisher(&broker);

    cout << "\n--- EVENT 1 ---\n";
    publisher.publish("OrderCreated", "Order #123 created");

    cout << "\n--- EVENT 2 ---\n";
    publisher.publish("PaymentSuccess", "Payment done for Order #123");

    cout << "\n--- EVENT 3 ---\n";
    publisher.publish("Refund", "Refund initiated");

    // Cleanup
    delete user1;
    delete user2;
    delete user3;

    return 0;
}
