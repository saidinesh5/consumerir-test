#include <QVector>
#include <QDebug>

#include <hardware/hardware.h>
#include <hardware/consumerir.h>

using namespace std;


class ConsumerIRDevice {
    consumerir_device_t *m_dev;
    bool m_hasIR;

private: 
    void fetchSupportedFrequencies(){
        
    }

public:
    ConsumerIRDevice():
        m_dev(nullptr),
        m_hasIR(false)
    {
        int err;
        hw_module_t const* module;
        err = hw_get_module(CONSUMERIR_HARDWARE_MODULE_ID, &module);
        if (err != 0) {
            qDebug() << "Can't open consumer IR HW Module, error:" << err;
            return;
        }

        err = module->methods->open(module, CONSUMERIR_TRANSMITTER, (hw_device_t **) &m_dev);

        if (err < 0) {
            qDebug() << "Can't open consumer IR transmitter, error: %d" << err;
            return;
        }

        m_hasIR = true;
    }
        
    ~ConsumerIRDevice()
    {
        if(m_dev)
            ((hw_device_t*)m_dev)->close((hw_device_t*)m_dev);
    }

    bool hasIR() { return m_hasIR; }

    bool transmit(int carrierFrequency, const QVector<int> pattern)
    {
        if(!m_hasIR)
        {
            qDebug() << "Device is not ready yet. Did you open it first?";
            return false;

            m_dev->transmit(m_dev, carrierFrequency, pattern.data(), pattern.size());
            return true;
        }

        return true;
    }
};


int main(int argc, char **argv)
{
    ConsumerIRDevice device;
    qDebug() << "Loaded IR plugin via Hal: " << device.hasIR();

    return 0;
}
