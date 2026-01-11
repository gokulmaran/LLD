#include <bits/stdc++.h>
using namespace std;

/* =========================
   Product
   ========================= */
class Product {
public:
    string productId;
    string name;
    double price;

    Product() {}

    Product(string id, string name, double price)
        : productId(id), name(name), price(price) {}
};

/* =========================
   Inventory Item
   ========================= */
class InventoryItem {
public:
    Product product;
    int quantity;

    InventoryItem() : quantity(0) {}

    InventoryItem(Product p, int qty)
        : product(p), quantity(qty) {}
};

/* =========================
   Warehouse
   ========================= */
class Warehouse {
private:
    string warehouseId;
    unordered_map<string, InventoryItem> inventory;
    mutex mtx;

public:
    Warehouse(string id) : warehouseId(id) {}

    string getId() {
        return warehouseId;
    }

    void addStock(Product product, int qty) {
        lock_guard<mutex> lock(mtx);
        inventory[product.productId].product = product;
        inventory[product.productId].quantity += qty;
    }

    bool reserveStock(string productId, int qty) {
        lock_guard<mutex> lock(mtx);

        if (!inventory.count(productId)) return false;
        if (inventory[productId].quantity < qty) return false;

        inventory[productId].quantity -= qty;
        return true;
    }

    void releaseStock(string productId, int qty) {
        lock_guard<mutex> lock(mtx);
        inventory[productId].quantity += qty;
    }

    int getStock(string productId) {
        lock_guard<mutex> lock(mtx);
        if (!inventory.count(productId)) return 0;
        return inventory[productId].quantity;
    }
};

/* =========================
   Inventory Manager (Facade)
   ========================= */
class InventoryManager {
private:
    vector<Warehouse*> warehouses;

public:
    void addWarehouse(Warehouse* warehouse) {
        warehouses.push_back(warehouse);
    }

    bool reserveProduct(string productId, int qty) {
        for (auto wh : warehouses) {
            if (wh->reserveStock(productId, qty)) {
                return true;
            }
        }
        return false;
    }

    void releaseProduct(string productId, int qty) {
        for (auto wh : warehouses) {
            wh->releaseStock(productId, qty);
        }
    }

    int getTotalStock(string productId) {
        int total = 0;
        for (auto wh : warehouses) {
            total += wh->getStock(productId);
        }
        return total;
    }
};

/* =========================
   Order
   ========================= */
enum class OrderStatus {
    CREATED,
    CONFIRMED,
    CANCELLED
};

class Order {
public:
    string orderId;
    string productId;
    int quantity;
    OrderStatus status;

    Order(string oid, string pid, int qty)
        : orderId(oid), productId(pid),
          quantity(qty), status(OrderStatus::CREATED) {}
};

/* =========================
   Order Service
   ========================= */
class OrderService {
private:
    InventoryManager& inventoryManager;

public:
    OrderService(InventoryManager& im) : inventoryManager(im) {}

    bool placeOrder(Order& order) {
        if (inventoryManager.reserveProduct(order.productId, order.quantity)) {
            order.status = OrderStatus::CONFIRMED;
            return true;
        }
        return false;
    }

    void cancelOrder(Order& order) {
        if (order.status == OrderStatus::CONFIRMED) {
            inventoryManager.releaseProduct(order.productId, order.quantity);
            order.status = OrderStatus::CANCELLED;
        }
    }
};

/* =========================
   Main (Demo)
   ========================= */
int main() {
    // Products
    Product laptop("P1", "Laptop", 75000);
    Product phone("P2", "Phone", 30000);

    // Warehouses
    Warehouse w1("W1");
    Warehouse w2("W2");

    w1.addStock(laptop, 10);
    w2.addStock(laptop, 5);
    w1.addStock(phone, 20);

    // Inventory Manager
    InventoryManager inventoryManager;
    inventoryManager.addWarehouse(&w1);
    inventoryManager.addWarehouse(&w2);

    // Order Service
    OrderService orderService(inventoryManager);

    // Place Order
    Order order1("O1", "P1", 10);

    if (orderService.placeOrder(order1)) {
        cout << "Order placed successfully\n";
    } else {
        cout << "Order failed due to insufficient stock\n";
    }

    cout << "Remaining Laptop Stock: "
         << inventoryManager.getTotalStock("P1") << endl;

    // Cancel Order
    orderService.cancelOrder(order1);

    cout << "After cancellation, Laptop Stock: "
         << inventoryManager.getTotalStock("P1") << endl;

    return 0;
}
