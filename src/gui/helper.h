#ifndef HELPER_H
#define HELPER_H

#include <model/qbeacon.h>
#include <model/qmeasure.h>
#include <QModelIndex>
#include <QIcon>

#define SIGNAL_OFF_ICON QIcon(":/resources/icons/antenna_off.png")
#define SIGNAL_ON_ICON QIcon(":/resources/icons/antenna_on.png")
namespace Gui {
    inline QBeacon qBeaconFromQModelIndex(const QModelIndex& index) {
        const QVariant data = index.data(Qt::UserRole);
        return data.canConvert<QBeacon>() ? data.value<QBeacon>() : QBeacon();
    }

    inline bool validateUuid(const QString& uuid) {
        static const QRegExp validator("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}");
        return uuid.contains(validator);
    }

    inline QwtData hiperbolicChart(const Position& center, Real radius, Size size) {
        const Real x0 = center(0);
        const Real y0 = center(1);
        const Real residual = radius * radius - x0 * x0;

        const Size halfSize = size / 2;
        const Vector xPoints = arma::linspace(x0-radius, x0+radius, halfSize);
        QwtData chart(size);
        for (Size i=0; i<size; i++) {
            if (i < halfSize) {
                chart.yData(i) = y0 - std::sqrt(residual - xPoints(i)*xPoints(i) + 2*xPoints(i)*x0);
                chart.xData(i) = xPoints(i);
            } else {
                chart.yData(i) = y0 + std::sqrt(residual - xPoints(i-halfSize)*xPoints(i-halfSize) + 2*xPoints(i-halfSize)*x0);
                chart.xData(i) = xPoints(i-halfSize);
            }
        }
        return chart;
    }


    void plot(const Vector &y);
    void plot(QwtData data);
}

#endif // HELPER_H
