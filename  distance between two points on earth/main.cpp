#include <stdio.h>
#include<math.h>

long double toRadians(const long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                      pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371*1000;
    ans = ans * R;

    return ans;
}

int main()
{
    long double lat1 = 53.32055555555556;
    long double long1 = -1.7297222222222221;
    long double lat2 = 53.31861111111111;
    long double long2 = -1.6997222222222223;
    printf(" Distance %Lf Meters",distance(lat1, long1,
                                               lat2, long2));
    return 0;
}
