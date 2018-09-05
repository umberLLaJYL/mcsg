#ifndef _DEVICE_H
#define _DEVICE_H

/**
 * Abstract base class: Device.
 */
class Device {

private:
    size_t countAbnormality;
    size_t runtime;

    string information;
    string status;

    map<string, GPIO> pin;
    
public:
    Device() = default;
    Device(const string &conf);
    ~Device();

    const string &getInformation() const;
    const string &getStatus() const;

    bool isChange() const;

    virtual void start() = 0;

protected:
    void pinInitialize() const;

    virtual void operate() = 0;
    virtual void analyse() = 0;

};
class Device;

#endif
