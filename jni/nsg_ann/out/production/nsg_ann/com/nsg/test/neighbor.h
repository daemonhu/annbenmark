namespace efanna2e {

class Neighbor {
public:
    unsigned id;
    float distance;
    bool flag;

    Neighbor() = default;
    Neighbor(unsigned id, float distance, bool f) : id{id}, distance{distance}, flag(f) {}

   // inline bool operator<(const Neighbor &other) const {
   //     return distance < other.distance;
   // }
};
}
