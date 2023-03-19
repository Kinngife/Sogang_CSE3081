#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <string>
#include <map>
#include <stack>
#include <queue>
using namespace std;
typedef struct node
{
    char ch;
    int cnt;
    struct node *left;
    struct node *right;
} Node;

struct cmp
{
    bool operator()(Node *a, Node *b)
    {
        return a->cnt > b->cnt;
    }
};

int main(int argc, char **argv)
{
    char *command = argv[1];
    char *infile = argv[2];
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        cout << "file error!\n";
        return 0;
    }

    char outfile[50] = "";
    strcat(outfile, infile);

    if (!strcmp(command, "-c"))
    {
        strcat(outfile, ".zz");

        map<char, int> m;
        map<char, int>::iterator iter;
        while (1)
        {
            char tmp = fgetc(input);
            if (tmp == EOF)
                break;
            if (m.find(tmp) != m.end())
                m[tmp]++;
            else
                m.insert({tmp, 1});
        }
        fclose(input);

        priority_queue<Node *, vector<Node *>, cmp> pq;
        for (iter = m.begin(); iter != m.end(); iter++)
        {
            Node *newnode = (Node *)malloc(sizeof(Node));
            newnode->ch = iter->first;
            newnode->cnt = iter->second;
            newnode->left = NULL;
            newnode->right = NULL;
            pq.push(newnode);
        }

        while (pq.size() > 1)
        {
            Node *node1 = pq.top();
            pq.pop();
            Node *node2 = pq.top();
            pq.pop();
            Node *node3 = (Node *)malloc(sizeof(Node));
            node3->ch = '0';
            node3->cnt = node1->cnt + node2->cnt;
            node3->left = node1;
            node3->right = node2;
            pq.push(node3);
        }
        Node *tree = pq.top();
        pq.pop();

        string huffman_code = "";
        map<char, string> convert_code;
        map<char, string>::iterator iter2;
        stack<pair<Node *, string> > st;
        st.push({tree, ""});
        while (!st.empty())
        {
            Node *cur = st.top().first;
            string s = st.top().second;
            st.pop();

            if (cur->left != NULL)
                st.push({cur->left, s + "0"});
            if (cur->right != NULL)
                st.push({cur->right, s + "1"});
            if (cur->left == NULL && cur->right == NULL)
                convert_code[cur->ch] = s;
        }
        if (m.size() == 1)
            convert_code[tree->ch] = "0";

        input = fopen(infile, "r");
        while (1)
        {
            char tmp = fgetc(input);
            if (tmp == EOF)
                break;
            huffman_code += convert_code[tmp];
        }

        // cout << huffman_code << "\n";
        FILE *result = fopen(outfile, "wb");

        fprintf(result, "%ld %ld\n", huffman_code.size(), convert_code.size());
        // printf("%ld %ld\n", huffman_code.size(), convert_code.size());

        for (iter2 = convert_code.begin(); iter2 != convert_code.end(); iter2++)
        {
            fprintf(result, "%d %ld\n", iter2->first, iter2->second.length());
            // printf("%d %ld\n", iter->first, iter->second.length());
        }
        map<char, string>::iterator iter3;
        for (iter3 = convert_code.begin(); iter3 != convert_code.end(); iter3++)
        {
            string s = iter3->second;
            for (int i = 0; i < s.length(); i++)
            {
                fprintf(result, "%c", s[i]);
                // printf("%c", s[i]);
            }
        }

        unsigned char buffer = 0;
        int cnt = 0;
        for (int i = 0; i < huffman_code.size(); i++)
        {
            buffer = buffer << 1;
            buffer = buffer | (huffman_code[i] - '0');
            cnt++;

            if (cnt == 8)
            {
                fprintf(result, "%c", buffer);
                // printf("%d", buffer);
                buffer = 0;
                cnt = 0;
            }
        }
        for (int i = cnt; i < 8; i++)
            buffer = buffer << 1;
        fprintf(result, "%c", buffer);
        // printf("%d\n", buffer);

        fclose(result);
        fclose(input);
    }
    else if (!strcmp(command, "-d"))
    {
        strcat(outfile, ".yy");

        int codesize, codecnt;
        fscanf(input, "%d %d\n", &codesize, &codecnt);
        // printf("%d %d\n", codesize, codecnt);

        vector<pair<pair<char, int>, string> > convert_code(codecnt);
        int sum = 0;
        for (int i = 0; i < codecnt; i++)
        {
            fscanf(input, "%hhd %d\n", &convert_code[i].first.first, &convert_code[i].first.second);
            // printf("%d %d\n", convert_code[i].first.first, convert_code[i].first.second);
            sum += convert_code[i].first.second;
        }
        // cout << sum << "\n";

        string s = "";
        for (int i = 0; i < sum; i++)
        {
            char tmp = fgetc(input);
            s += tmp;
        }
        // cout << s << "\n";

        int k = 0;
        for (int i = 0; i < codecnt; i++)
        {
            int num = convert_code[i].first.second;
            string tmp = "";
            for (int j = k; j < k + num; j++)
                tmp += s[j];
            k += num;
            convert_code[i].second = tmp;
        }
        // for (int i = 0; i < codecnt; i++)
        //     cout << convert_code[i].first.first << " : " << convert_code[i].second << "\n";

        string huffman_code = "";
        int buffer_size = codesize / 8;
        if (codesize % 8 != 0)
            buffer_size++;
        // cout << buffer_size << "\n";
        for (int i = 0; i < buffer_size; i++)
        {
            char c = fgetc(input);
            unsigned char tmp = (unsigned char)c;
            // printf("%d\n", tmp);
            unsigned char cmp = 128;
            for (int i = 0; i < 8; i++)
            {
                if ((int)(tmp & cmp) == 0)
                    huffman_code += '0';
                else
                    huffman_code += '1';
                tmp = tmp << 1;
            }
        }
        // cout << huffman_code.size() << "\n";
        // cout << huffman_code << "\n";
        // for (int i = 0; i < codesize; i++)
        //     cout << huffman_code[i];
        // cout << "\n";

        FILE *result = fopen(outfile, "w");
        string part = "";
        for (int i = 0; i < codesize; i++)
        {
            part += huffman_code[i];
            for (int j = 0; j < codecnt; j++)
            {
                if (part == convert_code[j].second)
                {
                    // cout << convert_code[j].first.first;
                    fprintf(result, "%c", convert_code[j].first.first);
                    part = "";
                }
            }
        }
        // cout << "\n";
        fclose(result);
        fclose(input);
    }
    else
    {
        cout << "command error!\n";
        fclose(input);
        return 0;
    }
    return 0;
}